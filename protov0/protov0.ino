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
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);   
  lcd.print("pplayer :");
  lcd.setCursor(0,1);
  lcd.print("nplayer :");
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
  lcd.setCursor(0,0);   
  lcd.print("pplayer :");
  lcd.setCursor(0,1);
  lcd.print("nplayer :");
  lcd.setCursor(10,0);           
  lcd.print(a);
  lcd.setCursor(10,1);           
  lcd.print(b); 
  if (huskylens.available())
  {
    HUSKYLENSResult result = huskylens.read();
    mtmove(result);
  }
  else
  {
    edst();
  }
  
  delay(1000);
}
void mtmove(HUSKYLENSResult result)
{
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String()+F("ID NUMBER:")+result.ID);
    if (result.ID == 1 || result.ID == 2) {
      digitalWrite(6,HIGH);
      mStepper.step(stepv);
         
      delay(6000);        
      mStepper.step(-stepv);
      digitalWrite(6,LOW);
      a=a+1;
      lcd.clear();
    }
    else {
      digitalWrite(7,HIGH);
      delay(1000);
      digitalWrite(7,LOW);
      b=b+1;
      lcd.clear();
    }
  }

}
void edst()
{
  if (!huskylens.request()) natvque();
  else if (!huskylens.available()) natvavali();
}

void natvque(){
  
  Serial.println(F("카메라의 데이터가 전송되지 않습니다. 카메라 전원을 확인하여 주십시오."));
  
}
void natvavali(){
  Serial.println(F("데이터에 없습니다. 얼굴을 인식하여 주십시오."));
}
// 객체로 쓸수 있었는데 아깝다.......
