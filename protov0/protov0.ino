#include<Stepper.h>
#include"HUSKYLENS.h"
#include<Wire.h>
#include <LiquidCrystal_I2C.h>
HUSKYLENS huskylens;
void printResult(HUSKYLENSResult result);
const int stepv = 512;//각도 90도
Stepper mStepper(stepv,11,9,10,8);
int a=0,b=0;
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
  lcd.setCursor(10,0);           // 0번째 줄 0번째 셀부터 입력하게 합니다.
  lcd.print(a);
  lcd.setCursor(10,1);           // 1번째 줄 0번째 셀부터 입력하게 합니다.
  lcd.print(b); 
  
  if (!huskylens.request()) Serial.println(F("데이터가 요청되지 않았습니다.."));
  else if (!huskylens.isLearned()) Serial.println(F("읽을수없습니다."));
  else if (!huskylens.available()) Serial.println(F("이용가능하지 않습니다."));
  else
  {
    
    while (huskylens.available())
    {
      HUSKYLENSResult result = huskylens.read();
      ptdata(result);
    }
    
  }
  delay(1000);
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
