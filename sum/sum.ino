#include <Adafruit_ADS1X15.h>
#include <Wire.h>
#include <BfButton.h>
#include <BfButtonManager.h>

Adafruit_ADS1115 ads1115;

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
  Serial.begin(9600);
  Serial.println("Hello!");
  Serial.println("Getting single-ended readings from AIN0..3");
  ads1115.begin();

  //Gain을 조정하여 최대 6.144V의 전압에 대한 데이터를 출력하며, 1 bit당 0.1875mV의 전압으로 인식합니다.
  ads1115.setGain(GAIN_TWOTHIRDS);
  Serial.println("ADC Range: +/- 6.144V (1 bit = 0.1875mV)");
}
void ADS::ADS_loop()
{
  //입력 신호의 데이터를 저장할 변수를 선언합니다.


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

  Serial.print("AIN0: "); Serial.println(adc0);
  Serial.print("AIN0 Voltage : "); Serial.println(adc0 * 0.1875 / 1000 * 100); //5V를 500으로 설정하고자 100 곱함!
  Serial.print("AIN1: "); Serial.println(adc1);
  Serial.print("AIN1 Voltage : "); Serial.println(adc1 * 0.1875 / 1000 * 100);
  Serial.print("AIN2: "); Serial.println(adc2);
  Serial.print("AIN2 Voltage : "); Serial.println(adc2 * 0.1875 / 1000 * 100);
  Serial.print("AIN3: "); Serial.println(adc3);
  Serial.print("AIN3 Voltage : "); Serial.println(adc3 * 0.1875 / 1000 * 100);
  Serial.println(" ");

  //Serial.print("AIN4: "); Serial.println(adc4);
  //Serial.print("AIN5: "); Serial.println(adc5);
  //Serial.print("AIN6: "); Serial.println(adc6);
  //Serial.print("AIN7: "); Serial.println(adc7);
  delay(2000);
}


int Min;
int Max;
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
ADS A; //ADS class 객체 선언

//compare 함수
void compare()
{
  if (A.adc0 * 0.1875 / 1000 * 100 < Min || A.adc0 * 0.1875 / 1000 * 100 > Max)
  {
    pinMode(14, OUTPUT);
    digitalWrite(14, HIGH); //CH1 알람 울려라
    delay(1000);
  }
  if (A.adc1 * 0.1875 / 1000 * 100 < Min || A.adc1 * 0.1875 / 1000 * 100 > Max)
  {
    pinMode(15, OUTPUT);
    digitalWrite(15, HIGH); //CH2 알람 울려라
    delay(1000);
  }
  if (A.adc2 * 0.1875 / 1000 * 100 < Min || A.adc2 * 0.1875 / 1000 * 100 > Max)
  {
    pinMode(16, OUTPUT);
    digitalWrite(16, HIGH); //CH3 알람 울려라
    delay(1000);
    pinMode(29, INPUT);
    SwitchState = digitalRead(29);
    if (SwitchState == HIGH)
    {
      digitalWrite(16, LOW);
      digitalWrite(29, LOW);
      break;
    }
  }
  if (A.adc3 * 0.1875 / 1000 * 100 < Min || A.adc3 * 0.1875 / 1000 * 100 > Max)
  {
    pinMode(17, OUTPUT);
    digitalWrite(17, HIGH); //CH4 알람 울려라
    delay(1000);
  }
}

void setup()
{
  Serial.begin(9600);
  myro.rotary_setup();
  A.ADS_setup();
  A.ADS_loop();
  Serial.println(A.adc2 * 0.1875 / 1000 * 100);
  delay(5000);
}

void loop()
{
  myro.rotary_loop();
  compare();
}
