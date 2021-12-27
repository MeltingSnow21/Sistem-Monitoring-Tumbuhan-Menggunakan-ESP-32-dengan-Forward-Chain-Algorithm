// copy paste from your Info page Firmware confign. following 2 lines
#define BLYNK_TEMPLATE_ID "TMPL770sS8d7"
#define BLYNK_DEVICE_NAME "FINALLLLLL"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
//#define BLYNK_DEBU

#include "BlynkEdgent.h"
#include <Servo_ESP32.h>


#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include "DHT.h" //inisiasi library DHT
#define sensor 33 //mendefinisikan sensor di GPIO 5
#define tipe DHT11 //mendefinisikan sensor tipe DHT 11
DHT dht(sensor,tipe); //mendefinisikan sensor dan tipe dht yang digunakan


// the timer object
static const int servoPin = 12;
Servo_ESP32 servo; 
int kondisi = 0;
int angle =0;
int angleStep = 2;
int angleMin =0;
int angleMax = 180;

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD




int Tinggi_Air,Curah_Hujan,Cahaya,Tanah;
bool Kondisi_Pesan=0;
bool Kondisi_lcd=0;

int a,b;
float kelem;
float suhu;


void hujan()
{
  Curah_Hujan = analogRead(34);
  Blynk.virtualWrite(V0,Curah_Hujan);
}

void air()
{
  Tinggi_Air = analogRead(35);
  Blynk.virtualWrite(V1,Tinggi_Air);
}

void cahaya()
{
  Cahaya = analogRead(32);
  Blynk.virtualWrite(V2,Cahaya);
}


void suhulembap() {
  // put your main code here, to run repeatedly:
  kelem = dht.readHumidity();
  suhu = dht.readTemperature();
  a = kelem;
  b = suhu;
  Blynk.virtualWrite(V3,b);
  Blynk.virtualWrite(V4,a);
}

void tanah()
{
  Tanah = analogRead(39);
  Blynk.virtualWrite(V5,Tanah);
}




void buka_atap(){
      if(kondisi == 0){
    for(angle = 0; angle <= angleMax; angle +=angleStep) {
        servo.write(angle);
        delay(50);
        kondisi = 1;
    }
    }
}

void tutup_atap(){
        if(kondisi == 1){
    for(angle = 180; angle >= angleMin; angle -=angleStep) {
        servo.write(angle);
        delay(50);
        kondisi = 0;
    }
    }
}

void hidupkan_air(){
    digitalWrite(2,HIGH); 
}

void matikan_air(){
     digitalWrite(2,LOW); 
}

void lcd_air_habis(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print ( "Air Habis" );
}

void lcd_air_cukup(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print ( "Air Cukup" );
  Kondisi_lcd=0;
}



void pesan(){
        if (Kondisi_Pesan == 0){
               Blynk.logEvent("air_habis", "Air didalam tank sudah hampir habis, namun cintaku padamu tidak") ;
             Kondisi_Pesan = 1;
        }
}



void Uji(){
  Serial.println("------------------------------------------");
  Serial.println("Pengujian");

  //RULES 1
  //tanah kering
     if(Tanah >3000){

      // tidak hujan 
      if (Curah_Hujan > 3000){
         hidupkan_air();
           Serial.println("Air hidup : tanah kering dan tidak hujan");
      }


  //RULES 2    
      //hujan
      else{
          //air mati
           matikan_air();
           Serial.println("Air mati : tanah kering dan hujan");
           //atap terbuka
           buka_atap();
           Serial.println("Atap terbuka: Hujan dan tanah kering");
      }
      
     }

  //RULES 3
  //tanah basah
     else{
      
        //matikan pompa; 
        matikan_air();
        Serial.println("Air mati : tanah basah");
     

  //RULES 4
        //hujan
        if(Curah_Hujan < 3000){
        //tutup atap
        Serial.println("Atap tertutup:  tanah basah dan Hujan");
        tutup_atap();
        }

  //RULES 4
        //tidak hujan
        else{
        //cahaya baik

        if (Cahaya >1500){
          //buka atap
                Serial.println("Atap terbuka:  tanah basah dan tidak Hujan serta cahaya baik");
        buka_atap();
        }
     }
     }

  //RULES 5
  //Tidak Hujan
     if (Curah_Hujan > 3000){
          
 
          //terlalu terang
          if (Cahaya <1500){
                  //tutup atap
                  tutup_atap();
                       Serial.println("Atap tertutup: Tidak hujan dan cahaya buruk");

          }

   //RULES 6        
          //cahaya bagus
          else{
                    //buka atap
                     Serial.println("Atap terbuka: Tidak hujan dan cahaya bagus");
                    buka_atap();
          }
                
         }

  //RULES 7
        //air habis
         if (Tinggi_Air <1700){
                lcd_air_habis();
                pesan();
                Kondisi_lcd=1;
         }

   //RULES 8        
         //air cukup
         else {
          //belum kirim
          if(Kondisi_lcd==1){
          lcd_air_cukup();
          }
          Kondisi_Pesan = 0;
         }
      

    Serial.println("");
    Serial.println("DATA");
    // Serial monitor     
    Serial.print("Tinggi air : " );
    Serial.println(Tinggi_Air);
    
    Serial.print("Curah hujan : ");
    Serial.println(Curah_Hujan);
       
    Serial.print("Cahaya : ");
    Serial.println(Cahaya);

    Serial.print("Tanah : ");
    Serial.println(Tanah);
  
    Serial.print(F("Kelembapan : "));
    Serial.println(a);
    Serial.print(F("% suhu : "));
    Serial.print(b);
    Serial.print(F(" C "));
    Serial.println("");
   Serial.println("--------------------------------------------------");

    
}

void setup()
{

  
  Serial.begin(115200);
  delay(500);
  dht.begin();
  servo.attach(servoPin);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  delay(100);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(2, OUTPUT);
  digitalWrite(2,LOW); 

  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print ( "chako" );

  
  BlynkEdgent.begin();
  timer.setInterval(500L,air);
  timer.setInterval(500L,hujan);
  timer.setInterval(500L,cahaya);
  timer.setInterval(500L,tanah);
  timer.setInterval(500L,suhulembap);

}

void loop() {
  BlynkEdgent.run();
  Uji();
  timer.run();
}
