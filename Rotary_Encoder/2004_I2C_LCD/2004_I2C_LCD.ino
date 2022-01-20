#include <LiquidCrystal_I2C.h>

/*
lcd 시리얼 테스트
아래링크에서 LiquidCrystal_I2C 라이브러리 다운로드
https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

www.mcuboard.com
*/
 
#include <LiquidCrystal_I2C.h> // LiquidCrystal_I2C 라이브러리 사용
 
// 객체이름을 lcd로 선언 I2C 주소값을 0x27로 설정, 16 문자 2줄 디스플레이
// 만약 lcd가 출력이 안된다면, 주소값을 0x27 혹은 0x3F로 수정
LiquidCrystal_I2C lcd(0x27, 20, 4);
 
void setup()
{
 lcd.begin(); // lcd 시작
 lcd.backlight(); // lcd 백라이트 on
  Serial.begin(9600); // 속도 9600bps로 시리얼 통신시작
 Serial.println("LCD통신 시작"); // 시리얼 통신 시작 문자 출력
}
 
void loop()
{
  
// 커서 설정(열,행) 0부터 시작
lcd.setCursor(0,0);
lcd.print("Hello"); 

lcd.setCursor(0,1);
lcd.print("Liquid");

lcd.setCursor(0,2);
lcd.print("Crystal");

lcd.setCursor(0,3);
lcd.print("Display");

}
