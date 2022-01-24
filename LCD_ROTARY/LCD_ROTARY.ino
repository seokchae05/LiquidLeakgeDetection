#include <Adafruit_ADS1X15.h>
#include <Wire.h>
#include "LCD12864RSPI.h"
#include "C:\Users\seokChae\Documents\Arduino\libraries\LCD12864RSPI\examples\LCD12864_test\DFrobot_bmp.h"
#include "C:\Users\seokChae\Documents\Arduino\libraries\LCD12864RSPI\examples\LCD12864_test\DFrobot_char.h"
#include <BfButton.h>
#include <BfButtonManager.h>

Adafruit_ADS1115 ads1115;

//ROTARY
int Min = 1;
int Max = 1;
int D5 = 5; //D5번 핀을 사용 (SW)
int D4 = 3; //D4번 핀을 사용 (DT)
int D3 = 4; //D3번 핀을 사용 (CLK)
int counter = 1; //rotary 회전 시 바뀜 (0~500까지의 값 설정)

//proximity
int val = 0;               // variable to store the values from sensor(initially zero)

BfButton btn(BfButton::STANDALONE_DIGITAL, D5, true, LOW);

void pressHandler(BfButton* btn, BfButton::press_pattern_t pattern)
{
  switch (pattern)
  {
    case BfButton::SINGLE_PRESS: //min 저장
      Serial.println("Single push");
      Min = counter;
      Serial.print("Min : ");
      Serial.println(Min);
      break;

    case BfButton::DOUBLE_PRESS:
      Serial.println("DOUBLE push");
      counter = 1;
      Serial.println(counter);
      break;

    case BfButton::LONG_PRESS: //max 저장
      Serial.println("LONG push");
      Max = counter;
      Serial.print("Max : ");
      Serial.println(Max);
      break;
  }
}

class ADS
{
  public:
    void ADS_setup();
    void ADS_loop();
    float adc0, adc1, adc2, adc3;
    float adc4, adc5, adc6, adc7;
};
void ADS::ADS_setup()
{
  //Serial.println("Hello!");
  //Serial.println("Getting single-ended readings from AIN0..3");
  ads1115.begin();

  //Gain을 조정하여 최대 6.144V의 전압에 대한 데이터를 출력하며, 1 bit당 0.1875mV의 전압으로 인식합니다.
  ads1115.setGain(GAIN_TWOTHIRDS);
  //Serial.println("ADC Range: +/- 6.144V (1 bit = 0.1875mV)");
}
void ADS::ADS_loop()
{
  //각 채널의 입력 신호를 읽고 변수에 저장합니다.

  adc0 = ads1115.readADC_SingleEnded(0);
  adc1 = ads1115.readADC_SingleEnded(1);
  adc2 = ads1115.readADC_SingleEnded(2);
  adc3 = ads1115.readADC_SingleEnded(3);


  //adc4 = ads1115.readADC_SingleEnded(9);
  //adc5 = ads1115.readADC_SingleEnded(5);
  //adc6 = ads1115.readADC_SingleEnded(6);
  //adc7 = ads1115.readADC_SingleEnded(7);

  //각 채널에 입력된 신호의 데이터를 출력합니다.
  //신호핀에 아무것도 연결되어 있지 않으면 의미 없는 값이 출력됩니다.
  //
  //  Serial.print("AIN0: "); Serial.println(adc0);
  //  Serial.print("AIN0 Voltage : "); Serial.println(adc0 * 0.1875 / 1000 * 100); //5V를 500으로 설정하고자 100 곱함!
  //  Serial.print("AIN1: "); Serial.println(adc1);
  //  Serial.print("AIN1 Voltage : "); Serial.println(adc1 * 0.1875 / 1000 * 100);
  //  Serial.print("AIN2: "); Serial.println(adc2);
  //  Serial.print("AIN2 Voltage : "); Serial.println(adc2 * 0.1875 / 1000 * 100);
  Serial.print("AIN3: "); Serial.println(adc3);
  //  Serial.print("AIN3 Voltage : "); Serial.println(adc3 * 0.1875 / 1000 * 100);
  //  Serial.println(" ");
}
class rotary
{
  public:
    int angle = 0;
    int aState;
    int aLastState;
    void rotary_setup();
    void rotary_loop();
};

//counter LCD 출력
int c = 1;
char* cnt; //counter
char * toArray_cnt(int number)
{
  int i;
  char *numberArray_cnt = calloc(c, sizeof(char));

  i = c - 1;
  while (i >= 0)
  {
    numberArray_cnt[i] = (number % 10) + '0';
    --i;
    number /= 10;
  }
  numberArray_cnt[c] = '\0';
  return numberArray_cnt;
}

void rotary::rotary_setup()
{
  Serial.println(angle);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  aLastState = digitalRead(D3);

  btn.onPress(pressHandler)
  .onDoublePress(pressHandler)
  .onPressFor(pressHandler, 1000);
}
void rotary::rotary_loop()
{
  btn.read();
  aState = digitalRead(D3);

  if (aState != aLastState)
  {
    if (digitalRead(D4) != aState)
    {
      counter++;
      angle++;
    }
    else
    {
      counter--;
      angle--;
    }
    if (counter >= 500)
    {
      counter = 500;
    }
    if (counter <= 1)
    {
      counter = 1;
    }
    Serial.println(counter);
    c = log10(counter) + 1;
    cnt = toArray_cnt(counter);

    LCDA.DisplayString(1, 1, "Cnt : ", 6);
    LCDA.DisplayString(1, 6, cnt, c);
    delete cnt;
  }
  aLastState = aState;
}

ADS myADS; //ADS class 객체 선언
rotary myro; //rotary class 객체 선언

//pinMode 설정
void pin()
{
  pinMode(14, OUTPUT); //CH1 알람
  pinMode(15, OUTPUT); //CH2 알람
  pinMode(16, OUTPUT); //CH3 알람
  pinMode(17, OUTPUT); //CH4 알람
  pinMode(9, INPUT); //proximity
}

//설정 범위와 측정값 비교 후 알람 울리기
void compare()
{
  Serial.println("hi");
  int AIN0_V = myADS.adc0 * 0.1875 / 1000 * 100;
  int AIN1_V = myADS.adc1 * 0.1875 / 1000 * 100;
  int AIN2_V = myADS.adc2 * 0.1875 / 1000 * 100;
  int AIN3_V = myADS.adc3 * 0.1875 / 1000 * 100;

  if (AIN0_V < Min || AIN0_V > Max && AIN1_V == 500 && AIN2_V == 500 && AIN3_V == 500)
  {
    if (Max != 1)
    {
      digitalWrite(14, HIGH); //CH1 알람 울려라
      // delay(1000);
    }
  }
  if (AIN1_V < Min || AIN1_V > Max && AIN0_V == 500 && AIN2_V == 500 && AIN3_V == 500)
  {
    if (Max != 1)
    {
      digitalWrite(15, HIGH); //CH2 알람 울려라
      // delay(1000);
    }
  }

  if (AIN2_V < Min || AIN2_V > Max && AIN0_V == 500 && AIN1_V == 500 && AIN3_V == 500)
  {
    if (Max != 1)
    {
      Serial.println("CH3 알람 울림");
      digitalWrite(16, HIGH); //CH3 알람 울려라
      //delay(1000);
      //pinMode(29, INPUT);
      //SwitchState = digitalRead(29);
      //if (SwitchState == HIGH)
      //{
      //  digitalWrite(16, LOW);
      // digitalWrite(29, LOW);
      //  break;
      //}
    }
  }

  if (AIN3_V < Min || AIN3_V > Max && AIN0_V == 500 && AIN1_V == 500 && AIN2_V == 500)
  {
    if (Max != 1)
    {
      digitalWrite(17, HIGH); //CH4 알람 울려라8
      //delay(1000);
    }
  }
}

//LCD
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )
unsigned char daha[] = "DAHA SYSTEMS"; //
unsigned char liquid[] = " Liquid Leak "; //
unsigned char detect[] = "Detector"; //

int n = 1;
int m = 1;

char* myc; //Max
char* myd; //Min

char * toArray_Max(int number)
{
  int i;
  char *numberArray_Max = calloc(n, sizeof(char));

  i = n - 1;
  while (i >= 0)
  {
    numberArray_Max[i] = (number % 10) + '0';
    --i;
    number /= 10;
  }
  numberArray_Max[n] = '\0';
  return numberArray_Max;
}
char * toArray_Min(int number)
{
  int i;
  char *numberArray_Min = calloc(m, sizeof(char));

  i = m - 1;
  while (i >= 0)
  {
    numberArray_Min[i] = (number % 10) + '0';
    --i;
    number /= 10;
  }
  numberArray_Min[m] = '\0';
  return numberArray_Min;
}

long time = millis();

void setup()
{
  Serial.begin(9600);
  myro.rotary_setup();

  LCDA.Initialise(); // INIT SCREEN
  delay(100);
  LCDA.DisplayString(0, 1, liquid, 12); //
  LCDA.DisplayString(1, 2, detect, 10); //
  LCDA.DisplayString(3, 1, daha, 12); //LOGO
  delay(5000);
  LCDA.CLEAR();//
  myADS.ADS_setup();
  pin();
}
void loop()
{
  val = digitalRead(9);
  if (time + 100 < millis())
  {

    myro.rotary_loop();
  }
  if (time + 450 < millis())
  {
    n = log10(Max) + 1;
    m = log10(Min) + 1;

    myc = toArray_Max(Max);
    myd = toArray_Min(Min);


    LCDA.DisplayString(2, 1, "Max : ", 6);
    LCDA.DisplayString(2, 6, myc, n);
    LCDA.DisplayString(3, 1, "Min : ", 6);
    LCDA.DisplayString(3, 6, myd, m);

    delete myc;
    delete myd;
  }
  if (time + 700 < millis())
  {
    time = millis();
    if (val == 1) // prox가 1이면 실행 되게
    {
      myADS.ADS_loop();
      Serial.println("prox 실행됨");
      compare();
    }
  }
}
