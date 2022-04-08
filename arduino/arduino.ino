//include the libraries
#include <dht.h>
//#include <LiquidCrystal_I2C.h>
//#include <Wire.h> 

dht DHT;//create a variable type of dht
//LiquidCrystal_I2C lcd(0x27,16,2); 

int   DHT11_PIN = A3;
int   BA_PIN    = A4;
int   PS_PIN    = A5;
float BA_Volt   = 0.0;
float PS_Volt   = 0.0;


void setup()
{
  pinMode(DHT11_PIN,INPUT);//set the state of D5 as INPUT
  pinMode(PS_PIN,INPUT);//set the state of A0 as INPUT
  pinMode(BA_PIN,INPUT);//set the state of A1 as INPUT
  
  Serial.begin(9600); //initialize the serial
//  lcd.init(); //initialize the lcd
//  lcd.backlight(); //open the backlight 
  
}
  
void loop()
{
  analogRead(PS_PIN); 
  delay(20);
  PS_Volt = analogRead(PS_PIN) * (4.7 / 1024.0) * 4.0;
  delay(30);
  analogRead(BA_PIN); 
  delay(20);
  BA_Volt = analogRead(BA_PIN) * (4.7 / 1024.0) * 4.0;
  
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

//    lcd.clear();
//    
//    lcd.setCursor(0, 0);
//    lcd.print("T:");
//    lcd.print((DHT.temperature *1.8) + 32, 1); //print the temperature on lcd
//    lcd.print(char(223));//print the unit" ℃ "
//    lcd.print("F");
//    
//    lcd.setCursor(9, 0);
//    lcd.print("H:");
//    lcd.print(DHT.humidity, 1); //print the humidity on lcd
//    lcd.print("%"); 
//  
//    lcd.setCursor(0, 1);
//    lcd.print("PS:");
//    lcd.print(PS_Volt,1);
//    lcd.print("V");
//  
//    lcd.setCursor(9, 1);
//    lcd.print("B:");
//    lcd.print(BA_Volt,1);
//    lcd.print("V");
    delay(1000);
  } 
}
