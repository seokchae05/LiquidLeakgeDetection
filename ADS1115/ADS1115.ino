#include <Adafruit_ADS1X15.h>
#include <Wire.h>

//ADDR 핀에 아무것도 연결되어 있지 않을 때 기본 i2c 주소(0x48)를 사용하여 동작합니다.
Adafruit_ADS1115 ads1115;

//ADDR핀을 이용하여 i2c 주소를 변경하였을 때에는 아래 소스코드를 이용합니다.
//Adafruit_ADS1115 ads1115(0x49);



class ADS
{
public:
  void ADS_setup();
  void ADS_loop();
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
  float adc0, adc1, adc2, adc3;
  float adc4, adc5, adc6, adc7;

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

ADS A;

void setup()
{
  A.ADS_setup();
}
void loop()
{
  A.ADS_loop();
}
