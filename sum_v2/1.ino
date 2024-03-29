#include <Wire.h>
#include <LiquidCrystal.h>
#include <Bounce2.h>

#define SWITCH_PIN 10
#define DT_PIN 11
#define CLK_PIN 12

byte menuCursor[8] = {
  B01000, //  *
  B00100, //   *
  B00010, //    *
  B00001, //     *
  B00010, //    *
  B00100, //   *
  B01000, //  *
  B00000  //
};

char * menuItems[] = {"Exit Menu ", "Set Temp  ", "ITEM 3    ", "ITEM 4    ", "ITEM 5    "};
int menuNum = sizeof(menuItems)/sizeof(char *); // array size
int menuStep = 0;  // 메뉴 단계 (0:초기 화면, 1:1단계 메뉴, 2:2단계 메뉴)
int itemStep = 0;  // 메뉴 값 (0:초기 화면, 1:메뉴_1, 2:메뉴_2, 3:메뉴_3)

int setTemp = 25;  // 온도 설정값

int lcdCols = 16;
int lcdRows = 2;

LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

Bounce debouncer = Bounce();

void setup() {
  Serial.begin(9600);

  pinMode(SWITCH_PIN, INPUT_PULLUP);

  // Initializes and clears the LCD screen
  lcd.begin(lcdCols, lcdRows);
  lcd.clear();

  lcd.createChar(0, menuCursor);

  debouncer.attach(SWITCH_PIN);
  debouncer.interval(5); // interval in ms
}

void loop() {
  debouncer.update();  // Update the Bounce instance
  if(debouncer.fell()) menuStep++;  // 버튼이 클릭되면 1씩 증가

  if(menuStep == 0) displayScreen();
  else if(menuStep == 1) displayMenu();
  else if(menuStep >= 3) { displayMenu(); menuStep = 1; lcd.setCursor(12, 1); lcd.print("  "); }
  else {
    switch(itemStep) {
    case 1:
      menuItem1();
      break;
    case 2:
      menuItem2();
      break;
    case 3:
      menuItem3();
      break;
    case 4:
      menuItem4();
      break;
    case 5:
      menuItem5();
      break;
    default: 
      // if nothing else matches, do the default
      // default is optional
    break;
    }
  }
}

void menuItem1() {  // 메뉴에서 나감, 디스플레이 모드로
  menuStep = 0;
 itemStep = 0;
}

void menuItem2() {
  lcd.setCursor(12, 1); lcd.print(setTemp);
  int change = getEncoderTurn();
  setTemp = setTemp + change;
}

void menuItem3() {
}

void menuItem4() {
}

void menuItem5() {
}

void displayScreen() {
  lcd.setCursor(0, 0);
  lcd.print("HELLO WORLD");
  lcd.setCursor(0, 1);
  lcd.print("           ");
}

void displayMenu() {
  int change = getEncoderTurn();
  itemStep = itemStep + change;
  if(itemStep >= menuNum) itemStep = menuNum;
  else if(itemStep <= 1) itemStep = 1;

  if(itemStep <= lcdRows) { 
    lcd.setCursor(0, itemStep - 1); lcd.write(byte(0));
    lcd.setCursor(0, lcdRows - itemStep); lcd.print(" ");
  } else {
    lcd.setCursor(0, lcdRows - 1); lcd.write(byte(0));
  }

  if(itemStep == 1) {
    lcd.setCursor(1, 0);
    lcd.print(menuItems[0]);
    lcd.setCursor(1, 1);
    lcd.print(menuItems[itemStep]);
  } else {
    lcd.setCursor(1, 1);
    lcd.print(menuItems[itemStep - 1]);
  }
} 

int getEncoderTurn() {  // 로터리 엔코더 값 반환 (-1, 0, +1)
  static int oldInc = LOW;
  static int oldDec = LOW;
  int result = 0;
  int newInc = digitalRead(CLK_PIN);
  int newDec = digitalRead(DT_PIN);

  if (newInc != oldInc || newDec != oldDec) {
    if (oldInc == LOW && newInc == HIGH) {
      result = -(oldDec * 2 - 1);
    }
  }
  oldInc = newInc;
  oldDec = newDec;

  return result;
}
[출처] 1602 LCD와 로터리 엔코더를 이용한 메뉴 구현|작성자 해바우