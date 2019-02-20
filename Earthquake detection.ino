/*
scl sda of gyro a4 a5 respectievely
tX rX of GSM module D8 D9 
buzzer pin D2
gas sensor , brown wire A0 , red wire to vcc black wire to GND 
 */


#include <I2Cdev.h>
#include <SoftwareSerial.h>
#include <MPU6050.h>
#include <Wire.h>
#define maxgas 650
#define vibxm 13000
#define vibx 20000
#define vibym 2500
#define viby 2500
#define vibzm 1500
#define vibz 3500
#define buzzpin 2


SoftwareSerial sim800l(8, 9); // tX, rX of gsm 800l module
MPU6050 accelgyro;
int sensor=A0;
int gas_value;
int16_t ax, ay, az, gx, gy, gz;
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  pinMode(buzzpin,OUTPUT);
  sim800l.begin(9600);
  pinMode(sensor,INPUT);
  accelgyro.initialize();
  delay(500);
}
void loop() 
{

gyro();
gas_value=analogRead(sensor);
Serial.println(gas_value);
if(gas_value>=maxgas){SendTextMessageFire();}

}

void gyro()
{
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print(ax);   Serial.print("     ");
  Serial.print(ay);   Serial.print("     ");
  Serial.println(az);  Serial.print("     ");
 delay(100); 
   if(ax<=vibxm || ax>=vibx || ay<=-vibym || ay>=viby || az<=-vibzm || az>=vibz )
  {
    Serial.println(" Eartquake ");
    SendTextMessage(); 
  }  
}
void SendTextMessage()
{
  digitalWrite(buzzpin,HIGH);
  Serial.println("Sending Text...");
  sim800l.print("AT+CMGF=1\r");   // Set the gsm module to SMS mode
  delay(100);
  digitalWrite(buzzpin,LOW);
 
  sim800l.print("AT+CMGS=\"+918445103030\"\r");  //enter number
  delay(200);
  digitalWrite(buzzpin,HIGH);
  sim800l.print("Earthquake! Earthquake, ");
  sim800l.print(" Emergency!!! PLEASE HELP ");
  sim800l.print("\r"); 
  delay(500);
  digitalWrite(buzzpin,LOW);
  sim800l.print((char)26);// CTRL Z FOR SENDING MESSAGE
  delay(100);
  digitalWrite(buzzpin,HIGH);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(100); // to stop texting for 100 milliseconds ..
  digitalWrite(buzzpin,LOW);
    
}
void SendTextMessageFire()
{
  digitalWrite(buzzpin,HIGH);
  Serial.println("Sending Text...");
  sim800l.print("AT+CMGF=1\r");   // Set the gsm module to SMS mode
  delay(100);
 digitalWrite(buzzpin,LOW);
  sim800l.print("AT+CMGS=\"+918445103030\"\r");  //enter number
  delay(200);
  digitalWrite(buzzpin,HIGH);
  sim800l.print("Fire or Gas Lekage, ");
  sim800l.print(" Emergency!!! PLEASE HELP ");
  sim800l.print("\r"); 
  delay(500);
  digitalWrite(buzzpin,LOW);
  sim800l.print((char)26);// CTRL Z FOR SENDING MESSAGE
  delay(100);
  digitalWrite(buzzpin,HIGH);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(100); // to stop texting for 100 milliseconds ..   
  digitalWrite(buzzpin,LOW); 
}
