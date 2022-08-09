#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//-------------------------------------------------- Sunucu Ve Wifi yi tanımlama

char auth[] = "er-u2t517_ofjF5bTA2FZD1Qm8Ul9xoe";
char ssid[] = "Mr.ozdemir";
char pass[] = "123asd321";

//--------------------------------------------------- Pinleri ve değişkenleri tanımlama

#define ledP D7
#define pirPin D1
float suhu;
int dataAdc;
int pirValue;
int Nota = 262;
bool PirStatus = false;
int vPinValue = 0;
int roleStatus;

//-------------------------------------------------

SimpleTimer timer;

BLYNK_WRITE(V1)   // Hareket sensörünün aktifliği için butondan değer  okuma yapar. (Butona V1 adında sanal pin atanır)
{
  vPinValue = param.asInt();  // butondaki 0 veya 1 değerini okur


}


void setup() {

//Blynk serverine bağlantı prosedürleri
Serial.begin(9600);
delay(10);
Blynk.begin(auth, ssid, pass); // Fonksiyon hedef ağa sürekli bağlantı isteği atar. 
timer.setInterval(1000L,sendUpTime);
  
pinMode(ledP, OUTPUT);        /// Led ve Hareket algılayıcı tanımlanır
pinMode(pirValue, INPUT);


}

void sendUpTime() // İlgili ekrana Lm35 den gelen analog değeri yazan fonksiyon
{
  int C = int(suhu); // Suhu değişkenşindeki ondalıklı sayıyı int e çevirir 

Blynk.virtualWrite(V10, C); // Blynk a Sıcaklığı yazar


}



void loop() {

//---------------------------------------//Hareket sensörü ve Alarm sistemi 

pirValue = digitalRead(pirPin); // hareket sensöründeki pin okunur

Serial.print(pirValue);

  if(vPinValue == 1){   // Eğer Hareket sensörü aktif butonu açık ise
    
    if(pirValue){  // Hareket sensörüden gelen değer 1 ise

      

       Blynk.notify("Dikkat Hareket Algılandı!!!");   // uyarı mesajı verir ve alarm öter
       tone(D2,Nota);
       delay(10000);
       noTone(D2);
       

}
  }
  //------------------------------------------
    digitalWrite(ledP, pirValue);
  
  
    Temp(); // fonksiyonları çalıştırır
    sendUpTime();
}

void Temp(void){ // Lm 35 ten ısı değeri çeker

dataAdc = analogRead(A0); // analog değeri oku
suhu = dataAdc * (3.2 / 1023.0) * 100.0; // derece cinsine çevirir
}
