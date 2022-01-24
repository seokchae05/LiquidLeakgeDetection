
/*
  LCD  Arduino
  PIN1 = GND
  PIN2 = 5V
  RS(CS) = 8;
  RW(SID)= 9;
  EN(CLK) = 3;
  PIN15 PSB = GND;
*/
#include "LCD12864RSPI.h"
#include "C:\Users\seokChae\Documents\Arduino\libraries\LCD12864RSPI\examples\LCD12864_test\DFrobot_bmp.h"
#include "C:\Users\seokChae\Documents\Arduino\libraries\LCD12864RSPI\examples\LCD12864_test\DFrobot_char.h"

#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )




unsigned char daha[] = "DAHA SYSTEMS"; //

unsigned char liquid[] = " Liquid Leak "; //

unsigned char detect[] = "Detector"; //

int Min = 0 ;

//String myString = String(0);
int Max = 500;
int n = log10(Max) + 1;
char* myc;

char * toArray(int number)
{
    int i;
    char *numberArray = calloc(n, sizeof(char));

    i = n - 1;
    while(i >= 0)
    {
      numberArray[i] = (number % 10) + '0';
      --i;
      number /= 10;
    }
    numberArray[n] = '\0';
    return numberArray;
}

void setup()
{
  Serial.begin(9600);
  myc = toArray(Max);
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
  delay(100);
//  Serial.println("hello");
//  Serial.println(myc);
//  LCDA.DisplayString(0, 2, "sibal ", 8);
  LCDA.DisplayString(1, 2, myc, n);
}
