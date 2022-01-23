#include <BfButton.h>
#include <BfButtonManager.h>
#include <Adafruit_ADS1X15.h>
#include <Wire.h>

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
  // delay(2000);
}


int Min;
int Max;
const int D5 = 5; //D5번 핀을 사용 (SW)

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
      Serial.println(int(Min));
      break;

    case BfButton::DOUBLE_PRESS: //max 저장
      Serial.println("Double push");
      Max = counter;
      Serial.print("Max : ");
      Serial.println(int(Max));
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
    int aState = 0;
    int aLastState = 0;
    void rotary_setup();
    void rotary_loop();
};


void rotary::rotary_setup()
{

  //  Serial.println(angle);
  //  pinMode(D3, INPUT_PULLUP);
  //  pinMode(D4, INPUT_PULLUP);
  //  aLastState = digitalRead(D3);
  //
  //  btn.onPress(pressHandler)
  //  .onDoublePress(pressHandler)
  //  .onPressFor(pressHandler, 1000);
}
void rotary::rotary_loop()
{
  int D4 = 3; //D4번 핀을 사용 (DT)
  int D3 = 4; //D3번 핀을 사용 (CLK)
  btn.read();
  aState = digitalRead(D3);
  delay(1000);
  Serial.println(String(aState) + "," + String(counter) + "," + String(angle));
  Serial.println(String(D3) + "," + String(D4));
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

void pin()
{
  pinMode(14, OUTPUT); //CH1 알람
  pinMode(15, OUTPUT); //CH2 알람
  pinMode(16, OUTPUT); //CH3 알람
  pinMode(17, OUTPUT); //CH4 알람
}

//compare 함수
void compare()
{
  int AIN0_V = A.adc0 * 0.1875 / 1000 * 100;
  int AIN1_V = A.adc1 * 0.1875 / 1000 * 100;
  int AIN2_V = A.adc2 * 0.1875 / 1000 * 100;
  int AIN3_V = A.adc3 * 0.1875 / 1000 * 100;
  /*
    Serial.println(AIN0_V);
    Serial.println(AIN1_V);
    Serial.println(AIN2_V);
    Serial.println(AIN3_V);
    delay(5000);
  */
  if (AIN0_V < Min || AIN0_V > Max && AIN1_V == 500 && AIN2_V == 500 && AIN3_V == 500)
  {
    digitalWrite(14, HIGH); //CH1 알람 울려라
    // delay(1000);
  }
  if (AIN1_V < Min || AIN1_V > Max && AIN0_V == 500 && AIN2_V == 500 && AIN3_V == 500)
  {
    digitalWrite(15, HIGH); //CH2 알람 울려라
    // delay(1000);
  }

  if (AIN2_V < Min || AIN2_V > Max && AIN0_V == 500 && AIN1_V == 500 && AIN3_V == 500)
  {
    //Serial.println("CH3 알람 울림");
    //digitalWrite(16, HIGH); //CH3 알람 울려라
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

  if (AIN3_V < Min || AIN3_V > Max && AIN0_V == 500 && AIN1_V == 500 && AIN2_V == 500)
  {

    digitalWrite(17, HIGH); //CH4 알람 울려라8
    //delay(1000);
  }

}


void setup()
{
  Serial.begin(9600);
  myro.rotary_setup();
  A.ADS_setup();
  //pin();
  Serial.println(A.adc2 * 0.1875 / 1000 * 100);
}

void loop()
{
  A.ADS_loop();
  myro.rotary_loop();
  // compare();
}
