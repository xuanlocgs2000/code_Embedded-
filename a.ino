#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int buzzer = 11;
int PIR1 = 2;
int PIR2 = 3;
int PIR3 = 4;


void setup() {
  //define the Relay pin as output
  Serial.begin(9600);
  Serial.println("Khong co gi bat thuong");
  pinMode(buzzer, OUTPUT);
  //define the sensor pin as input
  pinMode(PIR1, INPUT);
  pinMode(PIR2, INPUT);
  pinMode(PIR3, INPUT);
  noTone(buzzer);
  lcd.begin(16, 2);                    
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Khong co gi bat");
  lcd.setCursor(0,1);
  lcd.print("thuong");
}

void loop() {
  int value1 = digitalRead(PIR1);
  int value2 = digitalRead(PIR2);
  int value3 = digitalRead(PIR3);
  if(value1 == HIGH){
    if(value1 == HIGH || value3 == HIGH){
      tone(buzzer, 1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Phat hien xam");
      lcd.setCursor(0,1);
      lcd.print("nhap");
      Serial.println("Phat hien xam nhap");
      delay(60000);
    }else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("khong co gi bat");
      lcd.setCursor(0,1);
      lcd.print("thuong");
      Serial.println("khong co gi bat thuong");
      noTone(buzzer);
      delay(1000);
    }
 }
}
