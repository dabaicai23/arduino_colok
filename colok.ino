#include <LiquidCrystal_I2C.h>
#include <DHT11.h> 
#include <LiquidCrystal.h>
#include <DS1302.h>
#include <Wire.h>
#include <string.h>
#include <stdio.h>
 

#define YEAR 0
#define MONTH 1
#define DAY 2
#define HOUR 3
#define MINUTE 4
#define SECOND 5
#define ALARM_ONE 1
#define ALARM_TWO 2

int ledPin = 13;
int pin = 8;
int colok = 12;
const int Pin_Sel = 9;         
const int Pin_Adj_down = 10;    
const int Pin_Adj_up = 11;
int sw_in;
int sw_down;
int sw_up;


int j = 1;
int time = 0;
int H = 0;
int M = 0;
int Y = 2017;
int D = 1;
int Mo = 1;
boolean onoff = LOW;
boolean timefix = LOW;
unsigned long buttonHoldTime = 0;
int buttonStateOld;
int buttonState;
int PirState = LOW;
int val = 0; 
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
DS1302 rtc(4,3,2);
DHT11 dht11(pin);
int i = 0;
//String daysOfWeek[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};



void getdatetime()
{
    lcd.begin(16,2);
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print(rtc.getTimeStr());
    lcd.print(" ");
    lcd.print(rtc.getDOWStr());
    lcd.setCursor(0,1);
    lcd.print(rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, '/'));
 

}
void printTH(){
    int err;
    float temp, humi;
    if((err=dht11.read(humi, temp))==0) {
      lcd.begin(16,2);
      lcd.backlight();
      lcd.setCursor(0,0);
      lcd.print("T:  ");
      lcd.print((int)temp);
      lcd.print("C");  
      lcd.setCursor(0,1);
      lcd.print("H:  ");
      lcd.print((int)humi);
      lcd.print("%");
      delay(2000);             
     }else {
      lcd.begin(16,2);
      lcd.print("Error No :");
      lcd.print(err);  
    }  
  
}
void setcolok()
{
     lcd.clear();
     lcd.begin(16,2);
     lcd.backlight();
     lcd.setCursor(0,0);
      lcd.print("colok: ");
      lcd.print(M);
      lcd.print(" Min");
    
     delay(2000);
     do{
        sw_in = digitalRead(Pin_Sel);
        sw_up = digitalRead(Pin_Adj_up);
        sw_down = digitalRead(Pin_Adj_down);
        if(sw_up == HIGH){
          M += 1;
        }else if(sw_down == HIGH){
          M -= 1;
        }
        if(M >= 60 || M < 0){
          M = 0;
        } 
          //lcd.begin(16,2);
           //lcd.backlight();
           lcd.setCursor(0,0);
          lcd.print("colok: ");
          lcd.print(M);
          lcd.print(" Min");
         delay(500);
     }while(sw_in == LOW);
   
     lcd.setCursor(0,2);
     do{
        sw_in = digitalRead(Pin_Sel);
        sw_up = digitalRead(Pin_Adj_up);
        sw_down = digitalRead(Pin_Adj_down);
        if(sw_up == HIGH){
          H += 1;
        }else if(sw_down == HIGH){
          H -= 1;
        }
        if(H >=24 || H <0){
          H = 0;
        }
           //lcd.begin(16,2);
           //lcd.backlight();
           lcd.setCursor(0,0);
          lcd.print("colok: ");
          lcd.print(H);
          lcd.print(" Hour");  
           delay(500);
     }while(sw_in == LOW);
}
void settime(){
      lcd.clear();
     lcd.begin(16,2);
     lcd.backlight();
     lcd.setCursor(0,0);
      lcd.print("Stetime: ");
      lcd.print(M);
      lcd.print(" Min");
    
     delay(2000);
     do{
        sw_in = digitalRead(Pin_Sel);
        sw_up = digitalRead(Pin_Adj_up);
        sw_down = digitalRead(Pin_Adj_down);
        if(sw_up == HIGH){
          M += 1;
        }else if(sw_down == HIGH){
          M -= 1;
        }
        if(M >= 60 || M < 0){
          M = 0;
        } 
          //lcd.begin(16,2);
           //lcd.backlight();
           lcd.setCursor(0,0);
          lcd.print("Settime: ");
          lcd.print(M);
          lcd.print(" Min");
         delay(500);
     }while(sw_in == LOW);
   
     lcd.setCursor(0,2);
     do{
        sw_in = digitalRead(Pin_Sel);
        sw_up = digitalRead(Pin_Adj_up);
        sw_down = digitalRead(Pin_Adj_down);
        if(sw_up == HIGH){
          H += 1;
        }else if(sw_down == HIGH){
          H -= 1;
        }
        if(H >=24 || H <0){
          H = 0;
        }
           //lcd.begin(16,2);
           //lcd.backlight();
           lcd.setCursor(0,0);
          lcd.print("Settime: ");
          lcd.print(H);
          lcd.print(" Hour");  
           delay(500);
     }while(sw_in == LOW);
     do{
        sw_in = digitalRead(Pin_Sel);
        sw_up = digitalRead(Pin_Adj_up);
        sw_down = digitalRead(Pin_Adj_down);
        if(sw_up == HIGH){
          Y += 1;
        }else if(sw_down == HIGH){
          Y -= 1;
        }
        if(Y >=2020 || Y <= 1995){
          Y = 1995;
        }
           //lcd.begin(16,2);
           //lcd.backlight();
           lcd.setCursor(0,0);
          lcd.print("Settime: ");
          lcd.print(Y);
          lcd.print(" Year");  
           delay(500);
     }while(sw_in == LOW);
     do{
        sw_in = digitalRead(Pin_Sel);
        sw_up = digitalRead(Pin_Adj_up);
        sw_down = digitalRead(Pin_Adj_down);
        if(sw_up == HIGH){
          Mo += 1;
        }else if(sw_down == HIGH){
          Mo -= 1;
        }
        if(H >=12 || H <=0){
          H = 1;
        }
           //lcd.begin(16,2);
           //lcd.backlight();
           lcd.setCursor(0,0);
          lcd.print("Settime: ");
          lcd.print(Mo);
          lcd.print(" Mon");  
           delay(500);
     }while(sw_in == LOW);
     do{
        sw_in = digitalRead(Pin_Sel);
        sw_up = digitalRead(Pin_Adj_up);
        sw_down = digitalRead(Pin_Adj_down);
        if(sw_up == HIGH){
          D += 1;
        }else if(sw_down == HIGH){
          D -= 1;
        }
        if(D >31 || H <=0){
          H = 1;
        }
           //lcd.begin(16,2);
           //lcd.backlight();
           lcd.setCursor(0,0);
          lcd.print("Settime: ");
          lcd.print(D);
          lcd.print(" Day");  
           delay(500);
     }while(sw_in == LOW);
      rtc.halt(false);
    rtc.writeProtect(false);
     rtc.setTime(H,M,00);
     rtc.setDate(D,Mo,Y);
     rtc.writeProtect(true);
}


void setup()
{
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
   
    pinMode(Pin_Sel, INPUT);
    pinMode(Pin_Adj_up, INPUT);
    pinMode(Pin_Adj_down, INPUT);
    pinMode(colok,OUTPUT);
    lcd.begin(16,2);
  
    rtc.halt(false);
    rtc.writeProtect(false);
   // rtc.setDOW(SATURDAY);
    //rtc.setTime(23,30,00);
    //rtc.setDate(19,6,2017);
    rtc.writeProtect(true);
    

}

void loop()
{
    digitalWrite(ledPin, HIGH); 
    getdatetime();
    delay(2000);
    printTH();
    sw_in = digitalRead(Pin_Sel);
    if(sw_in== HIGH){
      settime();
    }
   // Time t = rtc.time();
   
    //if(t.hr == H && t.min == M){
     // digitalWrite(12,HIGH);
     // delay(500);
     ///digitalWrite(12,LOW);
   // }
  String tim[8] = rtc.getTimeStr();
  //Serial.println(tim[8]);
  
      //lcd.noBacklight();
      //lcd.clear();
  

   delay(1000);
   digitalWrite(ledPin, LOW); 
}


