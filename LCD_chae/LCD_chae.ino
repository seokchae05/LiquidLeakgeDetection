#include <LiquidCrystal_I2C.h>

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int maxNum = 0;
int minNum = 0;


int buttonState = 0;
bool btnStatus = true;







void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin();
  // Print a message to the LCD.
  lcd.print("DaHa Systems");
  lcd.setCursor(0, 1);
  lcd.print("liquid detector");
  delay(2500);
  lcd.clear();
  Serial.begin(9600);
  
  pinMode(7, INPUT);
  
  
}

void loop() {
  buttonState = digitalRead(7);  
  // Serial.println(buttonState);
  
  
  if (buttonState == HIGH) {
    btnStatus = !btnStatus;
  }
  
  if (btnStatus){
    delay(300);
    lcd.setCursor(0, 0);
  	lcd.print("Maximum Voltage");
    lcd.setCursor(8, 1);
  	lcd.print(maxNum);
  }
  
  else{
    delay(300);
    lcd.setCursor(0, 0);
  	lcd.print("Minimum Voltage");
    lcd.setCursor(8, 1);
  	lcd.print(minNum);
  }
  
    // turn LED on
    // delay(1000);
//    lcd.setCursor(0, 0);
  //	lcd.print("MIN : ");
  	//lcd.print(minNum);
  //}
  /*else{
    // delay(1000);
    bool btnStatus = False;
  	lcd.setCursor(0, 0);
  	lcd.print("MAX : ");
  	lcd.print(maxNum);
  }*/
  
}
