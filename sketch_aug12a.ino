// Author: Giorgi Kavtaradze
// Date: 20.08.2023
/******************************/
#include <LiquidCrystal_I2C.h>

#define LM36DZ A0

using namespace std;

const int RELAY = 2;
int tempSensor;
LiquidCrystal_I2C lcd(0x27, 16, 2);

  
  

void relay();
void lcd_display();

void setup() {
 pinMode(RELAY, OUTPUT);
 digitalWrite(tempSensor, 1);

}

void relay(){
  double setTemp = 20.0;
  int tempSensor = analogRead(LM36DZ);
  float mv = (5000.0 * tempSensor) / 1023.0;
  float roomTemp = -1 * (mv - 500.0) / 10.0;



  if(setTemp >= roomTemp){
    digitalWrite(RELAY, 1);
  }else{
    digitalWrite(RELAY, 0);
  };

  delay(1000);

  return;
};

void lcd_display(){
  double setTemp = 20.0;
  int tempSensor = analogRead(LM36DZ);
  float mv = (5000.0 * tempSensor) / 1023.0;
  float roomTemp = -1 * (mv - 500.0) / 10.0;

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Set Temp = ");
  lcd.print(setTemp);

  lcd.setCursor(0, 1);
  lcd.print("Room temp = ");
  lcd.print(roomTemp);

  delay(1000);
  return;
}

void loop() {
 
  lcd_display();
  relay();
}
