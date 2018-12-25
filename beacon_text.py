#!/usr/bin/env python3

import serial
import socket
import os


# Variables Initialization
index_file_path = '/tmp/index.txt'
# usb_port_file   = '/dev/cu.usbserial-AK069VN2'
usb_port_file = '/dev/ttyUSB0'
t_temp          = "000"
t_humid         = "000"
t_ps_volt       = "000"
t_batt_volt     = "000"
t_cpu_temp      = "000"
t_b1            = "0"
t_b2            = "0"
t_b3            = "0"
t_b4            = "0"
t_b5            = "0"
t_b6            = "0"
t_b7            = "0"
t_b8            = "0"

# This checks if there is internet
try:
  timeout     = 2
  host        = "8.8.8.8"
  port        = 53
  socket.setdefaulttimeout(timeout)
  socket.socket(socket.AF_INET, socket.SOCK_STREAM).connect((host, port))
  t_b1        = "1"
except Exception as ex:
  pass


# Get CPU temprature
try:
  cpu_temp    = os.popen('vcgencmd measure_temp').readline()
  cpu_temp    = cpu_temp.replace("temp=","").replace("'C\n","")
  t_cpu_temp  = '{0:03d}'.format(int(float(cpu_temp) * 10))
except:
  pass


# Read the actual data from Arduino and construct beacon  
try:
  ser = serial.Serial(usb_port_file)
  ser.flushInput()
  data = str(ser.readline()).split('@')
  while True:
    if len(data) == 6 :
      t_temp          = '{0:03d}'.format(int(float(data[1]) * 10))
      # t_temp            = '{0:03d}'.format(int((float(data[1]) - 32) / .18))
      t_humid           = '{0:03d}'.format(int(float(data[2]) * 10))
      t_ps_volt         = '{0:03d}'.format(int(float(data[3]) * 10))
      t_batt_volt       = '{0:03d}'.format(int(float(data[4]) * 10))
      t_b2              = "1"
      break
except:
  pass


# This constructs the telemetry index number, incerement it and save to file.
if not os.path.exists(index_file_path):
  index_file = open(index_file_path, "w+")
  index_file.write("000")
index_file = open(index_file_path, 'r')
index = index_file.read()
index_file.close()
new_index = '{0:03d}'.format(int(index) + 1)
if int(new_index) > 999:
   new_index = "000"
index_file = open(index_file_path, 'w')
index_file.write(new_index)
index_file.close()

#construct sense bits
if int(t_ps_volt)   > 135 : t_b3 = "1"
if int(t_batt_volt) < 126 : t_b4 = "1"
if int(t_temp)      > 400 : t_b5 = "1"
if int(t_temp)      < 125 : t_b6 = "1"


print("T#{},{},{},{},{},{},{}{}{}{}{}{}00".format(index, t_temp, t_humid, t_ps_volt, t_batt_volt, t_cpu_temp, t_b1, t_b2, t_b3, t_b4, t_b5, t_b6))
print("")