#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int a=2,b=3;
void setup() {
  // I2C LCD를 초기화 합니다.. begin은 이제 없음
  lcd.init();
  // I2C LCD의 백라이트를 켜줍니다.
  lcd.backlight();
}
void loop() { 
  lcd.setCursor(0,0);           // 0번째 줄 0번째 셀부터 입력하게 합니다.
  lcd.print("nplayer :");       // 문구를 출력합니다.
  lcd.print(a);
  lcd.setCursor(0,1);           // 1번째 줄 0번째 셀부터 입력하게 합니다.
  lcd.print("pplayer :");     // 문구를 출력합니다. 
  lcd.print(b); 
  delay(1000);
  lcd.clear();
  a=a+1;
  b=a+1;
}
