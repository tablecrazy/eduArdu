#include <NewPing.h>  // go to Sketch --> Include Library --> Manage Libraries --> NewPing (test with 1.9.1v)
#include "Buzzer.h"
#include "Joystick.h"

#define US_TX 8
#define US_RX 4
#define MAX_DISTANCE   200 // max distance in cm

Buzzer Buzz(6);
Joystick Joy (A0, A1);

NewPing Sonar(US_TX, US_RX, MAX_DISTANCE);

void setup()
{
  Serial.begin(115200);
  delay(100);
}

int Sample;
int Button = 1;
int Buzz_ON = 0;
int Duration;
void loop()
{
  while (Joy.But () && Button)
  {
    Button = 0;
    Buzz.Mute ();
    Buzz_ON = !Buzz_ON;
  }
  if (!Joy.But ())
    Button = 1;
  Sample = Sonar.ping_cm ();
  Serial.print(Sample);
  Serial.println(" cm");
  if (Buzz_ON)
  {
    if (Sample < 50)
    {
      Duration = 200 - (Sample * 3);
      Buzz.Note (880, Duration);
    }
    else
    {
      Duration = 50;
      Buzz.Note (440, Duration);
    }
  }
  delay(200 - Duration);
}