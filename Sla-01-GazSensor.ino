#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
/////////---------------------------------------------------Wifi ve sunucu tanımlamır
char auth[] = "er-u2t517_ofjF5bTA2FZD1Qm8Ul9xoe";
char ssid[] = "Mr.ozdemir";
char pass[] = "123asd321";

BlynkTimer timer;
 
int redLedPin = D1;
int sensorStatus = 0;
int vPinValue;
#define buzzer D4

BLYNK_WRITE(V2)   // Gaz sensörünün aktifliği için butondan değer  okuma yapar. (Butona V1 adında sanal pin atanır)
{
  vPinValue = param.asInt(); 
 
}


void setup() 
{
  pinMode(buzzer,OUTPUT); // buzzer tanımlanır
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(redLedPin, OUTPUT);     // led tanımlanır
 timer.setInterval(1000L, getSendData);
}


void loop() 
{
  
  timer.run(); 
  Blynk.run();

 }
void getSendData()// Gaz sensöründen gelen veriyi gönderir ve işler
{


sensorStatus = analogRead(A0); // Analog değeri okur

if(vPinValue == 1){       // eğer gaz sensörü aktif butonu açık ise
  if (sensorStatus > 300)   // gelen analog değer referans değerden yüksek ise
  {
    Blynk.notify("Dikkat !!! Gaz Sensörünüz Çalıştı");     // Blynka bildirim gider
  
    digitalWrite(redLedPin, HIGH);      // ikaz ışığı yanar
      digitalWrite(buzzer,HIGH);    // buzzer öter
  }

  else
  {

    digitalWrite(redLedPin, LOW);
    digitalWrite(buzzer,LOW);
  }
}
  
}
