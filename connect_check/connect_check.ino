int val = 0;
void setup() {
  Serial.begin(9600);
  pinMode(9, INPUT);
}

void loop() {
  val = digitalRead(9);
  Serial.println(val);
  delay(100);
}
