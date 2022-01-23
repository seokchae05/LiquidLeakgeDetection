#include <Arduino_FreeRTOS.h>
#include <semaphr.h>
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


char* int2char(int x)
{
  int i = 0, j = 0;
  int m[10];
  char out[10];
  do
  {
    m[i] = x % 10;
    x = x/10;
    i++;
  } while( x != 0);
  
  for(;i>=0;i--)
  {
    out[j] = m[i] + '0';
    j++;
  }

  return out;
}

int Min = 0 ;

//String myString = String(0);
int Max = 0;
char* myc = int2char(Max);

void setup()
{
  Serial.begin(9600);
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

  LCDA.DisplayString(0,0, "CH01", 4);
  LCDA.S
  LCDA.DisplayString(1,0, "CH02", 4);
  LCDA.DisplayString(2,0, "CH03", 4);
  LCDA.DisplayString(3,0, "CH04", 4);
  //delay(100);
//  Serial.println("hello");
//  Serial.println(myc);
//  LCDA.DisplayString(0, 2, "sibal ", 8);
//  LCDA.DisplayString(1, 2, myc, 16);

  
}
