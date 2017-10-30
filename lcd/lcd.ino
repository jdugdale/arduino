#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BACKLIGHT_PIN     13

LiquidCrystal_I2C lcd(0x27, 20, 4);
String kids[] = { "Annie", "Emily", "Lucy", "Ben" };
void setup() {
  Serial.begin(9600);
  //pinMode(23, INPUT);
  
  //pinMode(8, OUTPUT);
  //pinMode(9, OUTPUT);
  //pinMode(10, OUTPUT);
  //pinMode(53, OUTPUT);
  //pinMode(52, OUTPUT);

  //digitalWrite(53, HIGH);
  //digitalWrite(52, HIGH);

  lcd.init();
  lcd.backlight();
  lcd.print("Hello world");
  /*
    for(int i = 0; i < 4; i++) {
    lcd.setCursor(0,i);
    lcd.print(kids[i]);
    }
  */
  //while(!Serial);
  Serial.println("did it");

}

int curKid = 0;
int curLine = 0;
void loop() {
  
   int reading = analogRead(24);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 int voltage = reading * 5 / 1.024;
 //voltage /= 1024.0;
 Serial.print(voltage); Serial.println(" volts"); 
 int temperatureC = (voltage - 424)/ 6.25 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");
 
 // now convert to Fahrenheit
 int temperatureF = (temperatureC * 1.8) + 32;
 Serial.print(temperatureF); Serial.println(" degrees F");

  lcd.clear();
  lcd.print(temperatureF);
  lcd.print("F");
  //curLine++;
  //if (curLine > 3) curLine = 0;
  //lcd.setCursor(0, curLine);
  delay(5000);
  return;

  while (Serial.available() > 0) {
    //lcd.print("                    ");
    lcd.setCursor(0, curLine);
    String next = Serial.readStringUntil('\n');

    if (next == "red") {
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
    } else if (next == "yellow") {
      digitalWrite(9, HIGH);
      delay(1000);
      digitalWrite(9, LOW);
    } else if(next == "blue") {
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
    } else if (next == "off") {
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
    } else if (next == "cls") {
      lcd.clear();
      lcd.setCursor(0, 0);
      curLine = 0;
    } else if(next == "switch") {
      digitalWrite(52, HIGH);
    } else if(next == "noswitch") {
      digitalWrite(52, LOW);
    } else {
      lcd.clear();
      lcd.print(next);
      //curLine++;
      //if (curLine > 3) curLine = 0;
      lcd.setCursor(0, curLine);
    }

  }
  /*
    lcd.clear();
    lcd.setCursor(0,0);

    lcd.print(kids[curKid]);
    lcd.setCursor(2,1);
    lcd.print("Pigs");
    lcd.setCursor(2,2);
    lcd.print("Living room");
    Serial.print("again");
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    if(kids[curKid] == "Emily")
    digitalWrite(8, HIGH);
    else
    digitalWrite(9,HIGH);
    //lcd.scrollDisplayLeft();
    curKid++;
    if(curKid == 4)
    curKid = 0;
    delay(3000);
  */
  /*
    const String WORDS = "Hello beautiful";
    for(int i = 0; i< WORDS.length(); i++) {
    lcd.print(WORDS[i]);
    delay(500);
    }
  */
}


