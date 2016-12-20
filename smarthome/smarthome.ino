#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include<SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>
#define DHTPin 5

DHT dht(DHTPin,DHT11);

const int LDRpin=A0;
const int sliderPin=12;
const int ACpin=2;
const int pirPin=16;
char auth[]="e0cd6ad738e043f099c37e9c41b779f9";
char ssid[]="KARMAN SINGH";
char pass[]="parvinder";
SimpleTimer timer;
float t;

WidgetLCD lcd(V4);

void setup() {
  
Serial.begin(115200); 
pinMode(LDRpin,INPUT);
pinMode(pirPin,INPUT);
pinMode(sliderPin,OUTPUT);
pinMode(ACpin,OUTPUT);
Blynk.begin(auth,ssid,pass);
dht.begin();
delay(200);
timer.setInterval(1000L,sendsensor);
timer.setInterval(1000L,pirsensor);
lcd.clear();
lcd.print(1,0,"WELCOME TO HOME");

}

BLYNK_WRITE(V2)
{
  int brightness=param.asInt();
  analogWrite(sliderPin,brightness);
 }

 BLYNK_WRITE(V3)
{
  int timerValue=param.asInt();
  digitalWrite(ACpin,timerValue);
  lcd.clear();
  if(timerValue==1)
  {
    lcd.print(1, 0, "AC is ON");
    }
else
{
  lcd.print(1, 0, "AC is OFF");
  }

}     

void sendsensor()
{
  t = dht.readTemperature(); 
  
  if (isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V1, t);
   
 }
 
void pirsensor()
{
  int pirState=digitalRead(pirPin);
  if(pirState==1)
 {
     Blynk.notify("SOMEONE HAS ENTERED YOUR HOME!");
     pirState=0;
  }
  
 }
void loop() {
  Blynk.run();
  timer.run();
  
}
