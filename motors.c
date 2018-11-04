#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

#define RANGE	100
#define INITIAL_VALUE 0

#define MLS 2 // Motor Left Speed
#define MLD 3 // Motor Left Direction
#define MRS 4 // Motor Right Speed
#define MRD 5 // Motor Right Direction

void init_motors()
{
  wiringPiSetup();
  softPwmCreate(MLS, INITIAL_VALUE, RANGE);
  softPwmWrite(MLS, 0);
  pinMode(MLD, OUTPUT);
  digitalWrite(MLD, HIGH);
  softPwmCreate(MRS, INITIAL_VALUE, RANGE);
  softPwmWrite(MRS, 0);
  pinMode(MRD, OUTPUT);
  digitalWrite(MRD, HIGH);
}
void stop_motors()
{
  softPwmWrite(MLS, 0);
  softPwmWrite(MRS, 0);
  // exit(1);
}
double left_speed;
double right_speed;
void motors(double speed, double left_offset, double right_offset)
{
  left_speed = speed + left_offset;
  right_speed = speed + right_offset;
  if (left_speed < 0)  {
    softPwmWrite(MLS, (int) -left_speed);
    digitalWrite(MLD, 0);
  }
  else
  if (left_speed > 0)  {
    softPwmWrite(MLS, (int) left_speed);
    digitalWrite(MLD, 1);
  } 
  if (right_speed < 0)  {
    softPwmWrite(MRS, (int) -right_speed);
    digitalWrite(MRD, 0);
  }
  else
  if (right_speed > 0)  {
    softPwmWrite(MRS, (int) right_speed);
    digitalWrite(MRD, 1);
  }
}
