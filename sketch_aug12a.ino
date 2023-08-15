// Author: Giorgi Kavtaradze
// Date: 15.08.2023
/******************************/
#include <LiquidCrystal_I2C.h>

#define LM36DZ A0
int tempSensor;

int RELAY = 2;

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
 pinMode(RELAY, OUTPUT);

 lcd.init();
 lcd.backlight();

};

void loop() { 
  tempSensor = analogRead(LM36DZ); 
  float setTemp = 20.0;
  float mv = 5000.0 * tempSensor / 1023.0;         // measures in millivolts;
  float roomTemp = -1 * ((mv - 500.0)/ 10.0 );      // measures in celcius;


  lcd.blink();
  lcd.setCursor(0, 0);
  lcd.print("Set Temp = ");
  lcd.print(setTemp);


  lcd.setCursor(0, 1);
  lcd.print("Room Temp = ");
  lcd.print(roomTemp);

  if(setTemp >= roomTemp){
    digitalWrite(RELAY, 1);
  }else{
    digitalWrite(RELAY, 0);
  };

  delay(1000);
};
