#include<Stepper.h>
#include<Wire.h>
const int stepv = 103;//각도 90도
Stepper mStepper(stepv,11,9,10,8);
int Sw = 2;




void setup() {
  // put your setup code here, to run once:
  mStepper.setSpeed(28);//속도
  Serial.begin(9600);
  Wire.begin();
  pinMode(Sw,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(Sw) == HIGH)
  {
    mStepper.step(stepv);  
  }
}
