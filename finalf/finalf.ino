#include<Stepper.h>
#include"HUSKYLENS.h"
#include<Wire.h>
#include <LiquidCrystal_I2C.h>
HUSKYLENS huskylens;
const int stepv = 512;
Stepper mStepper(stepv,11,9,10,8);
int a=0,b=0,eds = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
class Stcerov
{
  private:
    int svl=0;
  public:
    Stcerov(int vam1){
      svl=vam1;    
    }
    void prtc();
};
void Stcerov::prtc(){
  digitalWrite(svl,HIGH);
  delay(1000);
  digitalWrite(svl,LOW);
  eds=svl;
}
Stcerov req(5);
Stcerov aval(6);
Stcerov bval(7);
void setup() {
  lcd.init();
  lcd.backlight();
  mStepper.setSpeed(28);
  Serial.begin(9600);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  Wire.begin();
  while(!huskylens.begin(Wire))
  {
    bval.prtc();
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
    req.prtc();
  }
  else if (!huskylens.available()) 
  {
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
      delay(3000);        
      mStepper.step(-stepv);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      a=a+1; 
    }
    else {
      digitalWrite(5,HIGH);
      digitalWrite(7,HIGH);
      delay(1000);
      digitalWrite(5,LOW);
      digitalWrite(7,LOW);
      b=b+1;
    }
  }
}
