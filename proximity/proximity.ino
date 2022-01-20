/*

int ledPin = 13; //LED anode connected to digital pin 13
int inputPin = 2; //infrared proximity switch connected to digital pin 2
int val = 0; //this variable will read the value from the sensor

void setup()
{
pinMode(ledPin, OUTPUT); //declare LED as output
pinMode(inputPin, INPUT); //declare infrared sensor as input
}

void loop(){

val = digitalRead(inputPin); // read input value

if (val == HIGH) { //check if the input is HIGH
digitalWrite(ledPin, LOW); //LED is off
} else {
digitalWrite(ledPin, HIGH); //LED is turned on
}

*/

//collects data from an analog sensor

int sensorPin = 13;                 // analog pin used to connect the sharp sensor
int val = 0;               // variable to store the values from sensor(initially zero)
int sda = 24;

void setup()
{
  Serial.begin(9600);               // starts the serial monitor
  pinMode(sensorPin, INPUT);
  pinMode(sda,OUTPUT);
}
 
void loop()
{
  val = digitalRead(sda);       // reads the value of the sharp sensor
  Serial.println(val);            // prints the value of the sensor to the serial monitor
  delay(100);                    // wait for this much time before printing next value
}
