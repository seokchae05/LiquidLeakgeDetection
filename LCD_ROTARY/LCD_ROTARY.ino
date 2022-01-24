#include "LCD12864RSPI.h"
#include "C:\Users\seokChae\Documents\Arduino\libraries\LCD12864RSPI\examples\LCD12864_test\DFrobot_bmp.h"
#include "C:\Users\seokChae\Documents\Arduino\libraries\LCD12864RSPI\examples\LCD12864_test\DFrobot_char.h"
#include <BfButton.h>
#include <BfButtonManager.h>

//ROTARY
int Min = 1;
int Max = 1;
int D5 = 5; //D5번 핀을 사용 (SW)
int D4 = 3; //D4번 핀을 사용 (DT)
int D3 = 4; //D3번 핀을 사용 (CLK)
int counter = 0; //rotary 회전 시 바뀜 (0~500까지의 값 설정)

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

    case BfButton::DOUBLE_PRESS: //max 저장
      Serial.println("Double push");
      Max = counter;
      Serial.print("Max : ");
      Serial.println(Max);
      break;

    case BfButton::LONG_PRESS:
      Serial.println("Long push");
      counter = 0;
      Serial.println(counter);
      break;
  }
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


void rotary::rotary_setup()
{
  Serial.begin(9600);
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
    if (counter <= 0)
    {
      counter = 0;
    }
    Serial.println(counter);
  }
  aLastState = aState;
}
rotary myro; //rotary class 객체 선언

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
}
void loop()
{
  if (time + 100 < millis())
  {
    myro.rotary_loop();
  }
  if (time + 200 < millis())
  {
    time = millis();
    n = log10(Max) + 1;
    m = log10(Min) + 1;
    myc = toArray_Max(Max);
    myd = toArray_Min(Min);
    LCDA.DisplayString(2, 1, "Max : ", 6);
    LCDA.DisplayString(2, 5, myc, n);
    LCDA.DisplayString(3, 1, "Min : ", 6);
    LCDA.DisplayString(3, 5, myd, m);
  }
}
