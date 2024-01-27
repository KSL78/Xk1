# Huskylens, Arduino
## 프로젝트 개요
* Huskylens, Arduino를 이용한 자동문 프로젝트
## 제작 목적 및 크드 참고
* 졸업작품 및 아두이노 심화학습
## 참여자
* 코드설계 및 코딩: 본인
## 기한
* 코드 설계: 2022/5~10
## 본 프로젝트 사용 기술 및 환경
* Lan: Arduino C++
* OS,Tool: Windows 11, Arduino, Huskylens, ArduinoIDE
## 주요 기능 목차
1. 얼굴인식기능 및 인식에 따른 모터 기능
2. Huskylens의 동작 상태에 따른 기능
3. LED 기능 class화
****
## 1. 얼굴인식기능 및 인식에 따른 모터 기능
```
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
```
****
* Huskylens에서 아두이노에 전송되는 값에 따라 모터 동작 및 LED동작 결정,LCD 표시 변경
****
## 2. Huskylens의 동작 상태에 따른 기능
```
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
```
****
* Huskylens의 동작 상태에 따라 LCD 표시 변경 및 대응가능
****
## 3. LED 기능 class화
```
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
```
****
* LED기능을 class화 하여 코드 절약 및 기능 구현 단순화
****
