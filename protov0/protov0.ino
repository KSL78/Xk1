#include<Stepper.h>
#include"HUSKYLENS.h"
#include<Wire.h>
#include <LiquidCrystal_I2C.h>
HUSKYLENS huskylens;
void printResult(HUSKYLENSResult result);
const int stepv = 512;//각도 90도
Stepper mStepper(stepv,11,9,10,8);
int a=0,b=0,eds = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
class Stcerov
{
  private:
    int str=0;
  public:
    Stcerov(int vam1){
      str=vam1;    
    }
    void prtc();
};
void Stcerov::prtc(){
  if (str == 1)
  {
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    delay(1000);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    eds=1;
    //"카메라의 데이터가 전송되지 않습니다. 카메라 전원을 확인하여 주십시오."
  }
  else if (str == 2)
  {
    digitalWrite(5,HIGH);
    digitalWrite(7,HIGH);
    delay(1000);
    digitalWrite(5,LOW);
    digitalWrite(7,LOW);
    eds=2;
    //"데이터에 없습니다. 얼굴을 인식하여 주십시오."
  }
  else if (str == 5)
  {
    digitalWrite(7,HIGH);
    delay(1000);
    digitalWrite(7,LOW);
  }
}
void setup() {
  lcd.init();
  lcd.backlight();
  mStepper.setSpeed(28);//속도
  Serial.begin(9600);
  pinMode(5,OUTPUT);//r
  pinMode(6,OUTPUT);//g
  pinMode(7,OUTPUT);//b
  Wire.begin();
  while(!huskylens.begin(Wire))
  {
    Stcerov bval(5);
    bval.prtc();
    eds=5;
    delay(100);
  }
}
void loop() {
  lcd.setCursor(0,0);   
  lcd.print("pp:");
  lcd.setCursor(0,1);
  lcd.print("np:");
  lcd.setCursor(3,0);           
  lcd.print(a);
  lcd.setCursor(3,1);           
  lcd.print(b);
  lcd.setCursor(9,0);   
  lcd.print("ec:");
  lcd.setCursor(12,0);   
  lcd.print(eds);
  lcd.setCursor(9,1);   
  lcd.print("p:");
  lcd.setCursor(12,1);   
  lcd.print("0");
  if (huskylens.available())
  {
    HUSKYLENSResult result = huskylens.read();
    mtmove(result);
    eds=0;
  }
  else if (!huskylens.request())
  {
    Stcerov req(1);
    req.prtc();
  }
  else if (!huskylens.available()) 
  {
    Stcerov aval(2);
    aval.prtc();
  } 
  delay(1000);
}
void mtmove(HUSKYLENSResult result)
{
  if (result.command == COMMAND_RETURN_BLOCK) {
    if (result.ID == 1 || result.ID == 2) {
      lcd.setCursor(12,1);   
      lcd.print(result.ID);
      digitalWrite(6,HIGH);
      digitalWrite(7,HIGH);
      mStepper.step(stepv);  
      delay(6000);        
      mStepper.step(-stepv);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      a=a+1; 
    }
    else {
      digitalWrite(5,HIGH);
      delay(1000);
      digitalWrite(5,LOW);
      b=b+1;
    }
  }
}
