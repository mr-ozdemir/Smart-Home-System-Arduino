#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


//----------------------------------------------------
char auth[] = "er-u2t517_ofjF5bTA2FZD1Qm8Ul9xoe"; // Blynk sunucu anahtarı
char ssid[] = "Mr.ozdemir";                       // Ev Wifi ismi
char pass[] = "123asd321";                        // Ev wifi Parola
//------------------------------------------------------


BlynkTimer timer;

 ///////////////////////// Pinlerin değişkenlere atanması
 
int soilSensor = D7;
int redLedPin = D1;
int buzzerPin = D4;
int sensorStatus = 0;
int msjCount = 0;




void setup() 
{
  pinMode(soilSensor,INPUT); // Sensörün karta tanıtımı
  pinMode(buzzerPin,OUTPUT); // Buzzerın karta tanıtımı
   
  Serial.begin(115200);       // Derleme esnasında kontrol için serial ekranı bağlantısı
  Blynk.begin(auth, ssid, pass);  // Blynk sunucularına bağlantı atar ve tanımlı wifiyer sürekli bağlanır.-
  pinMode(redLedPin, OUTPUT);     // İkaz ışığının karta tanıtımı tanıtımı
  timer.setInterval(1000L, sendDataBl);
}

void sendDataBl(){  // Sensörden gelen veriyi BLYNK a gönderen Fonksiyon 
  String msj1 = "Susuz";
  String msj2 = "Normal";
  if(sensorStatus == 1){
    Blynk.virtualWrite(V3,msj1);  // Sensörden gelen dijital değer "1" ise Susuz
       
    
  }

  else{
    
      Blynk.virtualWrite(V3,msj2); // Sensörden gelen dijital değer "0" ise Normal
  }
}
 
void loop() 
{

  timer.run();   // Blynk ve timerı çalıştır 
  Blynk.run();
  
  sensorStatus = digitalRead(D7); // sensörün değerini okur
    Serial.println(sensorStatus);   
  if(sensorStatus == 1){  // eğer değer 1 ise
    
    

     digitalWrite(redLedPin,HIGH);      // ışıkları yakar alarm verir ve Blynk a uyarı gönderir
     
    digitalWrite(buzzerPin,HIGH);
     delay(100);
    digitalWrite(buzzerPin,LOW);
      delay(5000);   
      
      if(msjCount == 0 || msjCount == 1 ){  // 2 den fazla mesaj göndermemesi için eğer mesaj değişkeni 0 veya 1 ise
  
            Blynk.notify("Topraklariniz Susuz"); // mesajı gönderir
             
            msjCount++;  // mesaj değişkenini artırır
      }
    
  }
else{
  digitalWrite(redLedPin,LOW);  // alarm ve ışığı söndürür
     
    digitalWrite(buzzerPin,LOW);
  
}
  
  }

  


 
