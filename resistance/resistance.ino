int pin1 = 24;
float value = 0;

void setup() {
  Serial.begin(9600); //pc모니터로 전압값을 쉽게 확인하기 위하여 시리얼 통신을 설정해줍니다.
  pinMode(pin1, INPUT);
}

void loop() {
  value = digitalRead(pin1);
  Serial.println(value);
  delay(1000);

}
