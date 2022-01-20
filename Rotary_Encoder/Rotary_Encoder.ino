#include <BfButton.h>
#include <BfButtonManager.h>


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

void setup()
{
    myro.rotary_setup();
}

void loop()
{
    myro.rotary_loop();
}
