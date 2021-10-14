#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int ledPin = 8;                // choose the pin for the LED
int inputPin1 = 2;               // choose the input pin (for PIR sensor)
int inputPin2 = 3;
int inputPin3 = 4;

int pirState1 = LOW;             // we start, assuming no motion detected
int pirState2 = LOW;
int pirState3 = LOW;

int val1 = 0;  
int val2 =0;
int val3 =0;

int buzz = 11;                  // buzzer pin at 11
SoftwareSerial mySerial(9, 10);

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin1, INPUT);     // declare sensor as input
  pinMode(inputPin2, INPUT); 
  pinMode(inputPin3, INPUT); 
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  pinMode(buzz, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val1 = digitalRead(inputPin1);  // read input value
  val2 = digitalRead(inputPin2);
  val3 = digitalRead(inputPin3);

  if(val2 == HIGH){
    if(val1 == HIGH || val3 == HIGH){
      digitalWrite(ledPin, HIGH);  // turn LED ON
      digitalWrite(buzz, HIGH); //ACTIVATE BUZZER
      
      if(pirState1 == LOW && pirState2 == LOW && pirState3 == LOW){
        Serial.println("PHAT HIEN CO CHUYEN  DONG BAT THUONG!\r\n\n");
        Serial.println("THONG BAO \r\n\n");
        lcd.setCursor(0, 0);
        lcd.print("Phat hien chuyen");
        lcd.setCursor(0, 1);
        lcd.print("dong");
        mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
        delay(100);
        mySerial.println("AT+CMGS=\"+919699449474\"\r"); // change to the phone number you using 
        delay(100);
        mySerial.println("CO SU XAM NHAP\r\n\n");//the content of the message
        delay(100);
        mySerial.println("GUI THANH CONG \r\n");//the stopping character
        delay(100);      
        // We only want to print on the output change, not state
        pirState1 = HIGH; 
        pirState2 = HIGH; 
        pirState3 = HIGH; 
      }
    }else{
      digitalWrite(ledPin, LOW); // turn LED OFF
      digitalWrite(buzz, LOW);  // turn off buzzer
      if (pirState1 == HIGH && pirState2 == HIGH && pirState3 == HIGH ){
        // we have just turned of
        Serial.println("CHUYEN DONG DA NGUNG! \r\n\n");
        lcd.setCursor(0, 0);
        lcd.print("chuyen dong da");
        lcd.setCursor(0,1);
        lcd.print("ngung");
        mySerial.println("AT+CNMI=2,2,0,0,0\r\n\n"); // AT Command to recieve a live SMS
        mySerial.println("GUI THANH CONG"); // AT Command to recieve a live SMS
        delay(1000);
        // We only want to print on the output change, not state
        pirState1 = LOW; 
        pirState2 = LOW;
        pirState3 = LOW;
      }
    }
  }
}
