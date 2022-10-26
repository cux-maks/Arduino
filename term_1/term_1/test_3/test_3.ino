#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // LCD패널에 사용되는 핀 설정
int lcd_key     = 0;
int adc_key_in  = 0;
int start_key   = 0;
#define btnRIGHT  3
#define btnUP     0
#define btnDOWN   1
#define btnLEFT   2
#define btnSELECT 4
#define btnNONE   5
int read_LCD_buttons() {
  adc_key_in = analogRead(0);                 // 키패드 값을 받음
  if (adc_key_in > 1000) return btnNONE;
  if (adc_key_in < 50)   return btnLEFT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnRIGHT;
  if (adc_key_in < 555)  return btnSELECT;
  if (adc_key_in < 790)  return btnDOWN;
  return btnNONE;
}

int a[7], b[7], temp;

void setup() {
  delay(3000); // 게임에서 마지막으로 입력된 값이 들어오는 걸 방지
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  lcd.begin(16, 2);               // 라이브러리 시작
  lcd.setCursor(0, 0);            // 첫번째 줄 LCD 커서 위치 설정
  lcd.print("ARROW GAME START");  // 첫번째 줄에 출력
  lcd.setCursor(0, 1);            // 두번째 줄 LCD 커서 위치 설정
  lcd.print("YES: To The Left");  // 첫번째 줄에 출력
}
void loop() {

  //game 시작 yes 눌러야 시작하도록 만듦
  start_key = read_LCD_buttons();   // 키패드 값을 읽음
  
  if (start_key == 2)
  {
    lcd.clear();
    lcd.print("Check");
    lcd.setCursor(0, 1);            // 두번째 줄 LCD 커서 위치 설정
    lcd.print("The Dotmatrix!");  // 첫번째 줄에 출력

    storeArrow(); //랜덤 숫자 만들어서 배열에 저장하는 동시에 저장하는 숫자를 화살표로 바꿔서 도트매트릭스에 출력

    lcd.clear();
    lcd.print("Your turn!");
    
    InputArrow();

    CompareArrow();
  }
  //lcd_key = read_LCD_buttons();   // 키패드 값을 읽음

 
}

void storeArrow()
{
  Serial.print("-------------------\n");
  for(int i=0; i<7; i++)
    {
      a[i] = random(4);
      //Serial.print(i, " : a[i]="); // 잘 저장되고 있는지 확인
      
      printArrow(a[i]); // 화살표 출력
    }
  Serial.print("-------------------\n");
}


void InputArrow()
{
  int temp = btnNONE;
  for(int i=0; i<7; i++)
    {
      bool Is_escape = false;
      while(temp == read_LCD_buttons() || read_LCD_buttons() == btnNONE){
        if(temp != read_LCD_buttons()){
          Is_escape = true;
        }
        if(read_LCD_buttons() != btnNONE && Is_escape == true){
          break;
        }
      }
      b[i] = read_LCD_buttons();
      temp = b[i];
      Serial.print(b[i]); // 잘 저장되고 있는지 확인
      printArrow(b[i]); // 화살표 출력
    }
}

void CompareArrow() // 두 배열 비교하는 함수
{
  for(int i=0; i<7; i++)
  {
    if(a[i] != b[i])
    {
      lcd.clear();
      lcd.print("FAIL!!");
      Serial.print("FAIL!!\n");
      lcd.setCursor(0, 1);
      lcd.print("NEXT: To The Left");
      
      lcd.clear();
      lcd.print("RESTART?");
      lcd.setCursor(0, 1);
      lcd.print("YES: To The Left");
      break;
    }

    if(i==6)
    {
      lcd.clear();
      lcd.print("SUCCESS!!");
      Serial.print("SUCCESS!!\n");
      lcd.setCursor(0, 1);
      lcd.print("NEXT: To The Left");

      lcd.clear();
      lcd.print("Turn off Alarm?");
      lcd.setCursor(0, 1);
      lcd.print("YES: To The Left");
    }
  }
}


void printArrow(int a)
{
  delay(500);  
  switch (a) 
  {              
    case 0: {
        Serial.print("Up\n"); //이걸 이제 시리얼 모니터가 아닌 도트 매트릭스에 출력
        // 시리얼 프린트 지우고
        // 도트매트릭스 함수 호출
        // 이때 도트매트릭스 함수를 따로 만들어서 번호에 해당하는 모양을 함수로 전달
        // 도트매트릭스 함수 : 받은 정수 case마다 다른 모양을 도트매트릭스에 출력
        break;
      }
    case 1: {
        Serial.print("Down\n");
        break;
      }
    case 2: {
        Serial.print("Left\n");
        break;
      }
    case 3: {
        Serial.print("Right\n");
        break;
      }
  }
}
