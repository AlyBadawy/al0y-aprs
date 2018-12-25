//include the libraries
#include <dht.h>
//#include <Wire.h> 

dht DHT;//create a variable type of dht

int   DHT11_PIN = 17;//Humiture sensor attach to pin5
int   BA_PIN    = A4;
int   PS_PIN    = A5;
float BA_Volt   = 0.0;
float PS_Volt   = 0.0;


void setup()
{
  pinMode(DHT11_PIN,INPUT);//set the state of D5 as INPUT
  pinMode(PS_PIN,INPUT);//set the state of A0 as INPUT
  pinMode(BA_PIN,INPUT);//set the state of A1 as INPUT
  
  Serial.begin(9600);//initialize the serial

  PS_Volt = analogRead(PS_PIN) * (5.0 / 1023.0) * 4;
  delay(20);
  BA_Volt = analogRead(BA_PIN) * (5.0 / 1023.0) * 4;
  
  int chk = DHT.read11(DHT11_PIN);//read the value returned from sensor
  if (chk == DHTLIB_OK) {
    String output = "DATA:@";
    output += String(DHT.temperature , 1);
    output += "@";
    output += String(DHT.humidity, 1);
    output += "@";
    output += String(PS_Volt, 1);
    output += "@";
    output += String(BA_Volt, 1);
    output += "@";
    Serial.println(output);
    pinMode(LED_BUILTIN, OUTPUT);
  }
}
  
void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
