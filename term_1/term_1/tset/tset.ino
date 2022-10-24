#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  // LCD패널에 사용되는 핀 설정
int push_btn = 24; //몰라
int push_flag = 0;
int count = 0;
int randNum;

void setup() {

  lcd.begin(16, 2);               // 라이브러리 시작
  lcd.setCursor(0, 0);
  pinMode(push_btn, INPUT_PULLUP);

}

void loop() {

  randNum = random(10, 30);

  if (digitalRead(push_btn) == 0) {
    if (push_flag == 0) {
      push_flag = 1;
      count++;
    } else {}
  } else {
    push_flag = 0;
  }

  lcd.setCursor(0, 0);
  lcd.print("Goal Number:");
  lcd.print(randNum);
  lcd.setCursor(9, 1);
  lcd.print(count);

  delay(1000);
  lcd.clear();

}
