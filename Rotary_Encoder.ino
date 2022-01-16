#include <BfButton.h>


int D5 = 5; //D5번 핀을 사용 (SW)
int D4 = 3; //D4번 핀을 사용 (DT)
int D3 = 4; //D3번 핀을 사용 (CLK)
BfButton btn(BfButton::STANDALONE_DIGITAL, D5, true, LOW);

int counter = 0;
int angle = 0;
int aState;
int aLastState;

void pressHandler (BfButton *btn, BfButton::press_pattern_t pattern)
{
  switch (pattern)
  {
    case BfButton::SINGLE_PRESS:
      Serial.println("Single push");
      break;

    case BfButton::DOUBLE_PRESS:
      Serial.println("Double push");
      break;

    case BfButton::LONG_PRESS:
      Serial.println("Long push");
      counter = 0;
      Serial.println(counter);
      break;
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.println(angle);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  //pinMode(LED_Pin, OUTPUT); //  LED_Pin 없음
  aLastState = digitalRead(D3);

  btn.onPress(pressHandler)
  .onDoublePress(pressHandler)
  .onPressFor(pressHandler, 1000);
}

void loop()
{
  int val = analogRead(A0);
  Serial.print("저항값");
  Serial.print(val);
  delay(1000);
  
  btn.read();
  //Serial.println("hello");
  //Serial.println(digitalRead(D3));
  //Serial.println(digitalRead(D4));
  //delay(500);
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

  //analogWrite(LED_Pin, counter); //LED_Pin 없음
}
