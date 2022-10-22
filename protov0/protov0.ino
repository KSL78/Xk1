#include<Stepper.h>
#include"HUSKYLENS.h"
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
HUSKYLENS huskylens;
void printResult(HUSKYLENSResult result);
const int stepv = 512;//각도 90도
Stepper mStepper(stepv,11,9,10,8);
int udt,cdt;
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  mStepper.setSpeed(28);//속도
  Serial.begin(9600);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
  Wire.begin();
  while(!huskylens.begin(Wire))
  {
    Serial.println(F("Begin failed"));
    delay(100);
  }
}

void loop() {
    while (huskylens.available())
    {
      HUSKYLENSResult result = huskylens.read();
      ptdata(result);
      
    }
  
}
void ptdata(HUSKYLENSResult result)
{
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String()+F("사용자 ID:")+result.ID);
    if (result.ID == 1 || result.ID == 2) {
      digitalWrite(6,HIGH);
      mStepper.step(stepv);
         
      delay(6000);        
      mStepper.step(-stepv);
      delay(2000);
      digitalWrite(6,LOW);
    }
    else {
      digitalWrite(7,HIGH);
      delay(1000);
      digitalWrite(7,LOW);
    }
  }

}
