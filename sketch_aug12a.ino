// Author: Giorgi Kavtaradze
// Date: 20.08.2023
/******************************/
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <Wire.h>

#define LM36DZ A0

using namespace std;

float SetTemp = 20.0;
const int RELAY = 2;
const int UP = 4;
const int DOWN = 5;
const int START = 6;
int count = 0;
int tempSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);


void lcd_display();
void relay();
void buttons();

void setup() {
 pinMode(RELAY, OUTPUT);
 pinMode(UP, INPUT);
 pinMode(DOWN, INPUT);
 pinMode(START, INPUT);
 digitalWrite(tempSensor, 1);
//  digitalWrite(RELAY, 0);
// lcd.init();
// lcd.backlight();
// buttons();

};

void lcd_display(){
  int tempSensor = analogRead(LM36DZ);
  float mv = (5000.0 * tempSensor)/1023.0;
  float HomeTemp = ((500.0 - mv)/10.0);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Set Temp = ");
  lcd.print(SetTemp);

  lcd.setCursor(0, 1);
  lcd.print("Home temp = ");
  lcd.print(HomeTemp);

  return;
};

void relay(){
  int tempSensor = analogRead(LM36DZ);
  float mv = (5000.0 * tempSensor)/1023.0;
  float HomeTemp = ((500.0 - mv)/10.0);

  if(HomeTemp >= SetTemp){
    digitalWrite(RELAY, 1);
  }else{
    digitalWrite(RELAY, 0);
  };

  return;
}

void buttons(){
  //lcd_display();
  lcd.clear();

  while(count == 0){
    lcd.setCursor(0, 0);
    lcd.print("Set temp = ");
    lcd.print(SetTemp);
    while(digitalRead(UP) == 1 && digitalRead(DOWN) == 1 && 
          digitalRead(START) == 1);

    if(digitalRead(UP) == 0){
      SetTemp++;
      while(digitalRead(UP) == 0);
    }else if(digitalRead(DOWN) == 0){
      SetTemp--;
      while(digitalRead(DOWN) == 0);
    }else if(digitalRead(START) == 0){
      
      if(count == 1){
        digitalRead(START);
        count = 0;
      }else{
        count = 1;
      };
    }else if(digitalRead(START) == 1){
      if(count == 0){
        digitalRead(START);
        count = 1;
      }else{
        count = 1;
      };
    }
    
  };
  return;
};


void loop(){
  lcd_display();
  relay();
  buttons();
};
