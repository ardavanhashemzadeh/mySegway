#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

#define RANGE	100
#define INITIAL_VALUE 0

int MLS = 2;
int MLD = 3;
int MRS = 4;
int MRD = 5;

void init_motors()
{
  wiringPiSetup();
  softPwmCreate(MLS, INITIAL_VALUE, RANGE);
  softPwmWrite(MLS, 0);
  pinMode(MLD, OUTPUT);
  digitalWrite(MLD, HIGH);

  // initialize right motor (pin4, 5 & 6)
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

// to come to me, drive pin 0&5 to some power
// to away from me, drive pin 2&4 to some power

// pin 0:LM+, 2:LM-, 3:LCE
// pin 5:RM+, 4:RM-, 6:RCE
// put M+ high & M- low will come to me
// put M+ low & M- High will away from me

  left_speed = speed + left_offset;
  right_speed = speed + right_offset;

  // left motor
  if (left_speed < 0)  {
    softPwmWrite(MLS, (int) -left_speed);
    digitalWrite(MLD, 0);
  }
  else
  if (left_speed > 0)  {
    softPwmWrite(MLS, (int) left_speed);
    digitalWrite(MLD, 1);
  }

  // right motor
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



