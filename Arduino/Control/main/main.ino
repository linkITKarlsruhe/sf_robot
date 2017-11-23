#include <Arduino.h>

#include <Servo.h>


Servo myservoA;
Servo myservoB;
Servo myservoC;
Servo myservoD;
Servo myservoE;
Servo myservoF;
Servo myservoG;

int i,pos,myspeed,myshow;
int sea,seb,sec,sed,see,sef,seg;
static int v=0;

String mycommand="";
static int mycomflag=1;

int bState = 0;
int cState = 0;

int lastPosition;
int actualPosition;



void setup()
{
  Serial.begin(9600);
  Serial.println("Robot is starting...");
  pinMode(13,INPUT);

  myshow=0;
  mycomflag=1;


  // Pin-attachment of the servos
  myservoA.attach(3);
  myservoB.attach(5);
  myservoC.attach(6);
  myservoD.attach(9);
  myservoE.attach(10);
  myservoF.attach(11);
  myservoG.attach(12);

  // The position of the servos after starting the robot.
  myservoA.write(88);
  myservoB.write(12);
  myservoC.write(85);
  myservoD.write(73);
  myservoE.write(10);
  myservoF.write(50);
  myservoG.write(50);

  int servoState = 0;
  Serial.println("Robot started.");
}

void loop()
{
   char charBuf[10];
   int zero = 0;


    String charac  = Serial.readStringUntil(':');
    if(charac.length() >= 1) {


    Serial.print("### Servo: ");
    Serial.print(charac);
    Serial.print(" wurde auf ");

    Serial.read(); //next character is comma, so skip it using this
    String inputValueString = Serial.readStringUntil(';');
    int inputValue = inputValueString.toInt();
    Serial.print(inputValue);
    Serial.print(" Grad bewegt. ###");
    Serial.println("");

    charac.toCharArray(charBuf, 10);
    char ch = charBuf[0];
    switch(ch)
    {


/*******************************************************************************
*               Servo A - controls this servo to a position                    *
*******************************************************************************/

      case 'a':
      if(inputValue >= -70 && inputValue <= 70) {
      zero = (inputValue * (-1)) + 88;
      myservoA.write(zero);
      inputValue = 0;
      int servoState = myservoA.read();
      Serial.println("Servo Position: ");
      Serial.println(servoState);
      }else {
        Serial.println("Servormotor A wurde außerhalb seines Bereiches angesteuert! -70 bis 70 Grad erlaubt.");
      }
      break;


/*******************************************************************************
*               Servo B - controls this servo to a position                    *
*******************************************************************************/

      case 'b':
      cState = myservoC.read();
      zero = inputValue + 12;
      Serial.println(cState);
      Serial.println(zero);

      if( ((cState >= 40 && cState < 60) && (zero >= 5 && zero <= 95)) or
          ((cState >= 60 && cState < 80) && (zero >=10 && zero <= 75)) or
          ((cState >= 80 && cState < 100) && (zero >=10 && zero <= 55)) or
          ((cState >= 100 && cState < 120) && (zero >=10 && zero <= 35)))
          {
          myservoB.write(zero);
      }else {
        Serial.println("Servormotor B wurde außerhalb seines Bereiches angesteuert!");
      }

      inputValue = 0;
      break;


/*******************************************************************************
*               Servo C - controls this servo to a position                    *
*******************************************************************************/

      case 'c':
      bState = myservoB.read();
      zero = inputValue + 85;

      if( ((zero >= 40 && zero < 60) && (bState >= 5 && bState <= 95)) or
          ((zero >= 60 && zero < 80) && (bState >=10 && bState <= 75)) or
          ((zero >= 80 && zero < 100) && (bState >=10 && bState <= 55)) or
          ((zero >= 100 && zero < 120) && (bState >=10 && bState <= 35)))
          {
          myservoC.write(zero);
      }else {
        Serial.println("Servormotor B wurde außerhalb seines Bereiches angesteuert!");
      }

      inputValue = 0;
      break;

/*******************************************************************************
*               Servo D - controls this servo to a position                    *
*******************************************************************************/


      case 'd':
      if(inputValue >= -73 && inputValue <= 107) {
        zero = (inputValue + 73);
        myservoD.write(zero);
        inputValue = 0;
      }else {
        Serial.println("Servormotor D wurde außerhalb seines Bereiches angesteuert! -73 bis 107 Grad erlaubt.");
      }

      break;


/*******************************************************************************
*               Servo E - controls this servo to a position                    *
*******************************************************************************/

      case 'e':
        if(inputValue >= -80 && inputValue <= 80) {
        zero = (inputValue + 90);
        myservoE.write(zero);
        inputValue = 0;
      }else {
        Serial.println("Servormotor E wurde außerhalb seines Bereiches angesteuert! -80 bis 80 Grad erlaubt.");
      }

      break;


/*******************************************************************************
*               Servo F - controls this servo to a position                    *
*******************************************************************************/
      case 'f':

        zero = (inputValue + 50);
        myservoF.write(zero);
        inputValue = 0;


      break;

/*******************************************************************************
*               Servo G - controls this servo to a position                    *
*******************************************************************************/

      case 'g':

        zero = (inputValue + 50);
        myservoG.write(zero);
        inputValue = 0;


      break;

/*******************************************************************************
*                       Servo G - grabs an object                              *
*******************************************************************************/

      // Servo F
      case 'x':
      // Öffnet die Klaue vollständig
      myservoG.write(50);
      lastPosition = 50;
      actualPosition = 50;

      for(int i = 50; i <= 130; i += 5) {
        myservoG.write(i);

        actualPosition = myservoG.read();

        Serial.print("LastPostion: ");
        Serial.println(lastPosition);
        Serial.print("ActualPosition: ");
        Serial.println(actualPosition);

        if(actualPosition < lastPosition) {
          break;
        }
        lastPosition += 5;

      }


      break;


    }

}

  }
