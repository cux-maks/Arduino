#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // LCD패널에 사용되는 핀 설정
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
int read_LCD_buttons() {
  adc_key_in = analogRead(0);                 // 키패드 값을 받음
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;
  return btnNONE;
}
void setup() {
  lcd.begin(16, 2);               // 라이브러리 시작
  lcd.setCursor(0, 0);            // 첫번째 줄 LCD 커서 위치 설정
  lcd.print("Push the buttons");  // 첫번째 줄에 출력
}
void loop() {
  lcd.setCursor(9, 1);            // 두번째 줄 LCD 커서 위치 설정
  lcd.print(millis() / 1000);     // 숫자 카운트 출력
  lcd.setCursor(0, 1);            // 두번째 줄 LCD 커서 위치 설정
  lcd_key = read_LCD_buttons();   // 키패드 값을 읽음
  switch (lcd_key) {              // 키패트 이름 출력
    case btnRIGHT: {
        lcd.print("RIGHT ");
        break;
      }
    case btnLEFT: {
        lcd.print("LEFT   ");
        break;
      }
    case btnUP: {
        lcd.print("UP    ");
        break;
      }
    case btnDOWN: {
        lcd.print("DOWN  ");
        break;
      }
    case btnSELECT: {
        lcd.print("SELECT");
        break;
      }
    case btnNONE: {
        lcd.print("NONE  ");
        break;
      }
  }
}
