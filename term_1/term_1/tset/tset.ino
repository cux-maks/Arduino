#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  // LCD패널에 사용되는 핀 설정
int push_btn = 8; //몰라
int push_flag = 0;
int count = 0;
long randNum;

void setup() {
  lcd.begin(16, 2);               // 라이브러리 시작
  lcd.setCursor(0, 0);            // 첫번째 줄 LCD 커서 위치 설정
  lcd.print("Push the buttons");  // 첫번째 줄에 출력
  randNum = random(10, 30);

  pinMode(push_btn, INPUT_PULLUP);
}

void loop(){
  
  if (digitalRead(push_btn) == 0){
    if(push_flag == 0){
      set_flag = 1;
      count++;
    }else{}
  }else{
    set_flag = 0;
  }
  
  lcd.setCursor(0,1);
  lcd.print("Goal Number : ");
  lcd.print(randNum);
  lcd.setCursor(9,1);
  lcd.print(count);

}
