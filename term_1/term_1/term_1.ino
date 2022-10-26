#define btnRIGHT  3
#define btnUP     0
#define btnDOWN   1
#define btnLEFT   2
#define btnSELECT 4
#define btnNONE   5

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int lcd_key = 0;
int adc_key_in = 0;
int start_key = 0;

int x_axis[] = {26, 27, 28, 29, 30, 31, 32, 33};
int y_axis[] = {34, 35, 36, 37, 38, 39, 40, 41};

int a[7], b[7], temp;

int speaker = 25; // 스피커 핀 번호

int up_btn = 20; // + 버튼 핀 번호
int up_flag = 0; // + 버튼 플래그

int down_btn = 21; // - 버튼 핀 번호
int down_flag = 0; // - 버튼 플래그

int set_btn = 22; // set 버튼 핀 번호
int set_flag = 0; // set버튼 플래그

int game1_btn = 24;
int game1_btn_flag = 0;

int h = 0; // 알람 시
int m = 0; // 알람 분
int s = 0; // 알람 초
int set_btn_state = 0; // set 버튼 상태

int game1_start = 0;
int game2_start = 0;

int button_timeMode = 23;//인터럽트핀
int timeMode_flag = 0; // 인터럽트핀 플래그

int hour_ = 0; // 현재 hour 입력 변수
int min_ = 0; // 현재 min 입력 변수
int sec_ = 0; // 현재 sec 입력 변수
int buf_t = 0; // 현재시간 설정 보정용 변수

int game_num = 0;
int count = 0;
int randNum = 0;

int flag_ = 0;

//up
int up[8][8] = {\
  {0, 0, 0, 1, 1, 0, 0, 0}, \
  {0, 0, 1, 1, 1, 1, 0, 0}, \
  {0, 1, 1, 1, 1, 1, 1, 0}, \
  {1, 1, 1, 1, 1, 1, 1, 1}, \
  {0, 0, 1, 1, 1, 1, 0, 0}, \
  {0, 0, 1, 1, 1, 1, 0, 0}, \
  {0, 0, 1, 1, 1, 1, 0, 0}, \
  {0, 0, 1, 1, 1, 1, 0, 0} \
};

//down
int down[8][8] = {\
  {0, 0, 1, 1, 1, 1, 0, 0}, \
  {0, 0, 1, 1, 1, 1, 0, 0}, \
  {0, 0, 1, 1, 1, 1, 0, 0}, \
  {0, 0, 1, 1, 1, 1, 0, 0}, \
  {1, 1, 1, 1, 1, 1, 1, 1}, \
  {0, 1, 1, 1, 1, 1, 1, 0}, \
  {0, 0, 1, 1, 1, 1, 0, 0}, \
  {0, 0, 0, 1, 1, 0, 0, 0} \
};

//right
int right[8][8] = {\
  {0, 0, 0, 0, 1, 0, 0, 0}, \
  {0, 0, 0, 0, 1, 1, 0, 0}, \
  {1, 1, 1, 1, 1, 1, 1, 0}, \
  {1, 1, 1, 1, 1, 1, 1, 1}, \
  {1, 1, 1, 1, 1, 1, 1, 1}, \
  {1, 1, 1, 1, 1, 1, 1, 0}, \
  {0, 0, 0, 0, 1, 1, 0, 0}, \
  {0, 0, 0, 0, 1, 0, 0, 0} \
};

//left
int left[8][8] = {\
  {0, 0, 0, 1, 0, 0, 0, 0}, \
  {0, 0, 1, 1, 0, 0, 0, 0}, \
  {0, 1, 1, 1, 1, 1, 1, 1}, \
  {1, 1, 1, 1, 1, 1, 1, 1}, \
  {1, 1, 1, 1, 1, 1, 1, 1}, \
  {0, 1, 1, 1, 1, 1, 1, 1}, \
  {0, 0, 1, 1, 0, 0, 0, 0}, \
  {0, 0, 0, 1, 0, 0, 0, 0} \
};

const byte segPin[8] = {49, 48, 47, 46, 45, 44, 43, 42}; //사용핀{a,b,c,d,e,f,g,dp} 순서대로임
const byte digitPin[6] = {A10, A11, A12, A13, A14, A15}; //segment 위치 핀
boolean state = false;//시간 출력형식 지정
extern volatile unsigned long timer0_millis; //타이머변수
unsigned long readTime; //현재타이머시간

//a,b,c,d,e,f,g 상태값
byte segValue[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, //0
  {0, 1, 1, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1}, //2
  {1, 1, 1, 1, 0, 0, 1}, //3
  {0, 1, 1, 0, 0, 1, 1}, //4
  {1, 0, 1, 1, 0, 1, 1}, //5
  {1, 0, 1, 1, 1, 1, 1}, //6
  {1, 1, 1, 0, 0, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 1}, //8
  {1, 1, 1, 1, 0, 1, 1} //9
};

void switchFn();
void segClear();
void segOutput(int d, int Number, int dp);
void segPrint(int a, int b, int c);
void storeArrow();
void InputArrow();
void print_Matrix(int n);
void printArrow(int a);
int CompareArrow();
int setTime(int time_, int term);
int checkTheAlarmTime(int j, int m, int s, int hour_r, int min_r, int sec_r);
int read_LCD_buttons();

void setup() {

  lcd.begin(16, 2);
  lcd.clear();

  pinMode(button_timeMode, INPUT_PULLUP); // 12/24시간제 버튼 핀 INPUT_PULLUP으로 설정

  for (int i = 0; i < 10; i++) { // 7-segment 각각 led 핀 output
    pinMode(segPin[i], OUTPUT);
  }

  for (int j = 0; j < 6; j++) { // 7-segment 각 자리 핀 output
    pinMode(digitPin[j], OUTPUT);
    digitalWrite(digitPin[j], HIGH);
  }

  for (int i = 0; i < 8; ++i) {
    pinMode(x_axis[i], OUTPUT);
    pinMode(y_axis[i], OUTPUT);
    digitalWrite(x_axis[i], LOW); //off
    digitalWrite(y_axis[i], HIGH); //off
  }

  pinMode(up_btn, INPUT_PULLUP); // + 버튼 INPUT_PULLUP으로 설정
  pinMode(down_btn, INPUT_PULLUP); // - 버튼 INPUT_PULLUP으로 설정
  pinMode(set_btn, INPUT_PULLUP); // set 버튼 INPUT_PULLUP으로 설정
  pinMode(speaker, OUTPUT); // 스피커 OUTPUT으로 설정

  segPrint(0, 0, 0);

}

void loop() {
  if (game_num == 0) {

    digitalWrite(speaker, LOW);

    lcd.clear();

    start_key = 0;

    if (digitalRead(set_btn) == 0) { // set 버튼을 누를 때 마다 set_btn_state가 0, 1, 2, 3, 4, 5, 6순으로 바뀜
      if (set_flag == 0) {
        if (set_btn_state == 0) set_btn_state = 1;
        else if (set_btn_state == 1) set_btn_state = 2;
        else if (set_btn_state == 2) { // set_btn_state가 2에서 3으로 변할 때, 현재시간 보정을 위한 변수 buf_t에 millis() / 1000 값을 대입한다.
          set_btn_state = 3;
          buf_t = millis() / 1000;
        }
        else if (set_btn_state == 3) set_btn_state = 4;
        else if (set_btn_state == 4) set_btn_state = 5;
        else if (set_btn_state == 5) set_btn_state = 6;
        else if (set_btn_state == 6) {
          set_btn_state = 0;

        }
        set_flag = 1;
      } else {}
    } else {
      set_flag = 0;
    }

    if (set_btn_state == 0) { // set_btn_state == 0일 때, 현재시간 hour_ 설정

      hour_ = setTime(hour_, 1); // setTime함수로 hour_값 설정
      hour_ = hour_ % 24;
      segPrint(hour_, min_, sec_); // segPrint함수로 7-세그먼트에 출력

    } else if (set_btn_state == 1) { // set_btn_state == 1 일때, 현재시간 min_ 설정

      min_ = setTime(min_, 1); // setTime함수로 min_값 설정
      min_ = min_ % 60;
      segPrint(hour_, min_, sec_); // segPrint함수로 7-세그먼트에 출력

    } else if (set_btn_state == 2) { // sec_ 설정

      sec_ = setTime(sec_, 10); // setTime함수로 sec_값 설정
      sec_ = sec_ % 60;
      segPrint(hour_, min_, sec_); // segPrint함수로 7-세그먼트에 출력

    } else if (set_btn_state == 3) { // 알람 h 설정

      h = setTime(h, 1); // setTime함수로 h 값 설정
      h = h % 60;
      segPrint(h, m, s); // segPrint함수로 7-세그먼트에 출력

    } else if (set_btn_state == 4) { // 알람 m 설정

      m = setTime(m, 1); // setTime함수로 m 값 설정
      m = m % 60;
      segPrint(h, m, s); // segPrint함수로 7-세그먼트에 출력

    } else if (set_btn_state == 5) { // 알람 s 설정

      s = setTime(s, 10); // setTime함수로 s 값 설정
      s = s % 60;
      segPrint(h, m, s); // segPrint함수로 7-세그먼트에 출력

    } else if (set_btn_state == 6) { // set_btn_state == 6 일때, 현재 시간 표시

      readTime = millis() / 1000; // 아두이노에서 시간 불러와서 readTime에 저장
      if (millis() >= 86400000) { // 만약 그 값이 86400000보다 크다면
        timer0_millis = 0; // timer0_millis를 0으로 설정
      }

      int sec_r = sec_ + readTime - buf_t; // 입력한 현재시간(sec) + 아두이노로부터 불러온 초 - 현재시간 보정용 변수를 sec_r에 저장
      int min_r = min_ + (sec_r / 60); // 입력한 현재시간(min) + 아두이노로부터 불러온 초를 min_r에 저장
      sec_r = sec_r % 60; // sec_r을 60으로 나눈 나머지를 sec_r에 저장
      int hour_r = hour_ + (min_r / 60); // 입력한 현재시간(hour) + 아두이노로부터 불러온 초를 hour_r에 저장
      min_r = min_r % 60; // min_r을 60으로 나눈 나머지를 min_r에 저장
      hour_r = hour_r % 24; // hour_r을 24로 나눈 나머지를 hour_r에 저장

      if (state == 0) segPrint(hour_r, min_r, sec_r); // segPrint함수로 현재시간 출력 - 24시간제
      else segPrint(hour_r % 12, min_r, sec_r); // segPrint함수로 현재시간 출력 - 12시간제

      up_flag = 0;
      down_flag = 0;

      game_num = checkTheAlarmTime(h, m, s, hour_r, min_r, sec_r); // 알람으로 설정한 시간과 현재 시간이 일치하는지 검사 및 일치하면 알람 울리기

    }

    switchFn(); // 12시 or 24시 출력 변경 함수 호출
  } else if (game_num == 1) { // 알람게임 1: 버튼 연타 게임

    tone(speaker, 1000, 5);

    if (digitalRead(game1_btn) == 0) {
      if (game1_btn_flag == 0) {
        game1_btn_flag = 1;
        count++;
      } else {}
    } else {
      game1_btn_flag = 0;
    }


    randomSeed(analogRead(A7));
    if (randNum == 0) randNum = random(analogRead(A7) % 20) + 30;

    lcd.setCursor(0, 0);
    lcd.print("Goal Number:");
    lcd.setCursor(14, 0);
    lcd.print(randNum);
    lcd.setCursor(9, 1);
    lcd.print(count);

    if (count == randNum) {
      game_num = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("     Clear!     ");
      delay(1500);
      lcd.setCursor(0, 0);
      lcd.print("                ");
      count = 0;
      randNum = 0;
    }

    readTime = millis() / 1000; // 아두이노에서 시간 불러와서 readTime에 저장
    if (millis() >= 86400000) { // 만약 그 값이 86400000보다 크다면
      timer0_millis = 0; // timer0_millis를 0으로 설정
    }

    int sec_r = sec_ + readTime - buf_t; // 입력한 현재시간(sec) + 아두이노로부터 불러온 초 - 현재시간 보정용 변수를 sec_r에 저장
    int min_r = min_ + (sec_r / 60); // 입력한 현재시간(min) + 아두이노로부터 불러온 초를 min_r에 저장
    sec_r = sec_r % 60; // sec_r을 60으로 나눈 나머지를 sec_r에 저장
    int hour_r = hour_ + (min_r / 60); // 입력한 현재시간(hour) + 아두이노로부터 불러온 초를 hour_r에 저장
    min_r = min_r % 60; // min_r을 60으로 나눈 나머지를 min_r에 저장
    hour_r = hour_r % 24; // hour_r을 24로 나눈 나머지를 hour_r에 저장

    if (state == 0) segPrint(hour_r, min_r, sec_r); // segPrint함수로 현재시간 출력 - 24시간제
    else segPrint(hour_r % 12, min_r, sec_r); // segPrint함수로 현재시간 출력 - 12시간제

  } else if (game_num == 2) {
    // 여기에 화살표 게임 들어갈거임
    if (game2_start == 0) {

      lcd.begin(16, 2);               // 라이브러리 시작
      lcd.setCursor(0, 0);            // 첫번째 줄 LCD 커서 위치 설정
      lcd.print("ARROW GAME START");  // 첫번째 줄에 출력
      lcd.setCursor(0, 1);            // 두번째 줄 LCD 커서 위치 설정
      lcd.print("YES: Click");  // 첫번째 줄에 출력
      start = 1;
    }
    tone(speaker, 1000, 5);

    start_key = read_LCD_buttons();   // 키패드 값을 읽음

    if (start_key == 4)
    {
      lcd.clear();
      lcd.print("Check");
      lcd.setCursor(0, 1);            // 두번째 줄 LCD 커서 위치 설정
      lcd.print("The Dotmatrix!");  // 첫번째 줄에 출력

      storeArrow(); //랜덤 숫자 만들어서 배열에 저장하는 동시에 저장하는 숫자를 화살표로 바꿔서 도트매트릭스에 출력

      lcd.clear();
      lcd.print("Your turn!");

      InputArrow();
      game_num = CompareArrow();

    }

  }

}

//12시 or 24시 출력 변경
void switchFn() {

  if (digitalRead(button_timeMode) == 0) {
    if (timeMode_flag == 0) {
      timeMode_flag = 1;
      state = !state;
    } else {}
  } else {
    timeMode_flag = 0;
  }

}

//LED 초기화
void segClear() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segPin[i], LOW);
  }
}
//LED 출력
void segOutput(int d, int Number, int dp) {
  segClear();
  digitalWrite(digitPin[d], LOW);
  for (int i = 0; i < 7; i++) {
    digitalWrite(segPin[i], segValue[Number][i]);
  }
  digitalWrite(segPin[7], dp);
  delayMicroseconds(1000);
  digitalWrite(digitPin[d], HIGH);
}
//알람 울릴 시간인지 체크하는 함수

int checkTheAlarmTime(int h, int m, int s, int hour_r, int min_r, int sec_r) {
  if (h == hour_r && m == min_r && s == sec_r) {
    //analogWrite(piezo, 128);
    if (flag_ == 0) {
      flag_ = 1;
      // game_num = random(1, 3);
      randomSeed(analogRead(A7));
      int ret = (random(analogRead(A7) % 100)) % 2 + 1;
      Serial.println(ret);
      return 2;
    } else {}

  } else {
    flag_ = 0;
    return 0;
  }
}

void segPrint(int a, int b, int c) { // 7-segment에 시, 분, 초 출력함수
  segOutput(5, c % 10, 0); //sec 1의 자리
  segOutput(4, c / 10, 0); //sec 10의 자리
  segOutput(3, b % 10, 1); //min 1의 자리
  segOutput(2, b / 10, 0); //min 10의 자리
  segOutput(1, a % 10, 1); //hour 1의 자리
  segOutput(0, a / 10, 0); //hour 10의 자리
}

int setTime(int time_, int term) { // time_을 전달받아 term만큼 변화시킨 뒤 time_값 반환하는 함수

  if (digitalRead(up_btn) == 0) { // + 버튼 누르면
    if (up_flag == 0) {
      up_flag = 1;
      time_ += term; // term 씩 증가
    } else {}
  } else if (digitalRead(down_btn) == 0) { // - 버튼 누르면
    if (down_flag == 0) {
      down_flag = 1;
      if (time_ > 0) time_ -= term; // term 씩 감소
    } else {}
  } else {
    up_flag = 0;
    down_flag = 0;
  }
  return time_;

}

void storeArrow()
{
  Serial.print("-------------------\n");
  for (int i = 0; i < 7; i++)
  {
    a[i] = random(analogRead(0) % 4);
    //Serial.print(i, " : a[i]="); // 잘 저장되고 있는지 확인

    printArrow(a[i]); // 화살표 출력

    readTime = millis() / 1000; // 아두이노에서 시간 불러와서 readTime에 저장
    if (millis() >= 86400000) { // 만약 그 값이 86400000보다 크다면
      timer0_millis = 0; // timer0_millis를 0으로 설정
    }

    int sec_r = sec_ + readTime - buf_t; // 입력한 현재시간(sec) + 아두이노로부터 불러온 초 - 현재시간 보정용 변수를 sec_r에 저장
    int min_r = min_ + (sec_r / 60); // 입력한 현재시간(min) + 아두이노로부터 불러온 초를 min_r에 저장
    sec_r = sec_r % 60; // sec_r을 60으로 나눈 나머지를 sec_r에 저장
    int hour_r = hour_ + (min_r / 60); // 입력한 현재시간(hour) + 아두이노로부터 불러온 초를 hour_r에 저장
    min_r = min_r % 60; // min_r을 60으로 나눈 나머지를 min_r에 저장
    hour_r = hour_r % 24; // hour_r을 24로 나눈 나머지를 hour_r에 저장

    if (state == 0) segPrint(hour_r, min_r, sec_r); // segPrint함수로 현재시간 출력 - 24시간제
    else segPrint(hour_r % 12, min_r, sec_r); // segPrint함수로 현재시간 출력 - 12시간제

  }
  Serial.print("-------------------\n");
}

void InputArrow()
{
  int temp = btnNONE;
  for (int i = 0; i < 7; i++)
  {
    bool Is_escape = false;
    while (temp == read_LCD_buttons() || read_LCD_buttons() == btnNONE) {
      if (temp != read_LCD_buttons()) {
        Is_escape = true;
      }
      if (read_LCD_buttons() != btnNONE && Is_escape == true) {
        break;
      }
      readTime = millis() / 1000; // 아두이노에서 시간 불러와서 readTime에 저장
      if (millis() >= 86400000) { // 만약 그 값이 86400000보다 크다면
        timer0_millis = 0; // timer0_millis를 0으로 설정
      }

      int sec_r = sec_ + readTime - buf_t; // 입력한 현재시간(sec) + 아두이노로부터 불러온 초 - 현재시간 보정용 변수를 sec_r에 저장
      int min_r = min_ + (sec_r / 60); // 입력한 현재시간(min) + 아두이노로부터 불러온 초를 min_r에 저장
      sec_r = sec_r % 60; // sec_r을 60으로 나눈 나머지를 sec_r에 저장
      int hour_r = hour_ + (min_r / 60); // 입력한 현재시간(hour) + 아두이노로부터 불러온 초를 hour_r에 저장
      min_r = min_r % 60; // min_r을 60으로 나눈 나머지를 min_r에 저장
      hour_r = hour_r % 24; // hour_r을 24로 나눈 나머지를 hour_r에 저장

      if (state == 0) segPrint(hour_r, min_r, sec_r); // segPrint함수로 현재시간 출력 - 24시간제
      else segPrint(hour_r % 12, min_r, sec_r); // segPrint함수로 현재시간 출력 - 12시간제
    }
    b[i] = read_LCD_buttons();
    temp = b[i];
    Serial.print(b[i]); // 잘 저장되고 있는지 확인
    printArrow(b[i]); // 화살표 출력
  }
}

int CompareArrow() // 두 배열 비교하는 함수
{
  int i = 0;
  bool Is_Fail = false;
  while (i < 7) {
    if (a[i] != b[i]) Is_Fail = true;
    i++;
  }

  if (!Is_Fail)
  {
    lcd.clear();
    lcd.print("SUCCESS!!");
    Serial.print("SUCCESS!!\n");
    lcd.setCursor(0, 1);
    lcd.print("Turn off: Click");
    while (1) {
      readTime = millis() / 1000; // 아두이노에서 시간 불러와서 readTime에 저장
      if (millis() >= 86400000) { // 만약 그 값이 86400000보다 크다면
        timer0_millis = 0; // timer0_millis를 0으로 설정
      }

      int sec_r = sec_ + readTime - buf_t; // 입력한 현재시간(sec) + 아두이노로부터 불러온 초 - 현재시간 보정용 변수를 sec_r에 저장
      int min_r = min_ + (sec_r / 60); // 입력한 현재시간(min) + 아두이노로부터 불러온 초를 min_r에 저장
      sec_r = sec_r % 60; // sec_r을 60으로 나눈 나머지를 sec_r에 저장
      int hour_r = hour_ + (min_r / 60); // 입력한 현재시간(hour) + 아두이노로부터 불러온 초를 hour_r에 저장
      min_r = min_r % 60; // min_r을 60으로 나눈 나머지를 min_r에 저장
      hour_r = hour_r % 24; // hour_r을 24로 나눈 나머지를 hour_r에 저장

      if (state == 0) segPrint(hour_r, min_r, sec_r); // segPrint함수로 현재시간 출력 - 24시간제
      else segPrint(hour_r % 12, min_r, sec_r); // segPrint함수로 현재시간 출력 - 12시간제
      if (read_LCD_buttons() == 4) break;
    }
    return 0;
  }
  else {
    lcd.clear();
    lcd.print("FAIL!!");
    Serial.print("FAIL!!\n");
    lcd.setCursor(0, 1);
    lcd.print("RESTART: Click");
    while (1) {
      readTime = millis() / 1000; // 아두이노에서 시간 불러와서 readTime에 저장
      if (millis() >= 86400000) { // 만약 그 값이 86400000보다 크다면
        timer0_millis = 0; // timer0_millis를 0으로 설정
      }

      int sec_r = sec_ + readTime - buf_t; // 입력한 현재시간(sec) + 아두이노로부터 불러온 초 - 현재시간 보정용 변수를 sec_r에 저장
      int min_r = min_ + (sec_r / 60); // 입력한 현재시간(min) + 아두이노로부터 불러온 초를 min_r에 저장
      sec_r = sec_r % 60; // sec_r을 60으로 나눈 나머지를 sec_r에 저장
      int hour_r = hour_ + (min_r / 60); // 입력한 현재시간(hour) + 아두이노로부터 불러온 초를 hour_r에 저장
      min_r = min_r % 60; // min_r을 60으로 나눈 나머지를 min_r에 저장
      hour_r = hour_r % 24; // hour_r을 24로 나눈 나머지를 hour_r에 저장

      if (state == 0) segPrint(hour_r, min_r, sec_r); // segPrint함수로 현재시간 출력 - 24시간제
      else segPrint(hour_r % 12, min_r, sec_r); // segPrint함수로 현재시간 출력 - 12시간제
      if (read_LCD_buttons() == 4) break;
    }
    return 2;
  }
}

void print_Matrix(int n) {

  switch (n) {
    case 0:
      for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
          if (up[i][j] == 1) {
            digitalWrite(x_axis[i], HIGH);
          } else {
            digitalWrite(x_axis[i], LOW);
          }
        }
        digitalWrite(y_axis[j], LOW);
        delayMicroseconds(350);
        digitalWrite(y_axis[j], HIGH);
      }
      break;
    case 1:
      for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
          if (down[i][j] == 1) {
            digitalWrite(x_axis[i], HIGH);
          } else {
            digitalWrite(x_axis[i], LOW);
          }
        }
        digitalWrite(y_axis[j], LOW);
        delayMicroseconds(350);
        digitalWrite(y_axis[j], HIGH);
      }
      break;
    case 2:
      for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
          if (left[i][j] == 1) {
            digitalWrite(x_axis[i], HIGH);
          } else {
            digitalWrite(x_axis[i], LOW);
          }
        }
        digitalWrite(y_axis[j], LOW);
        delayMicroseconds(350);
        digitalWrite(y_axis[j], HIGH);
      }
      break;
    case 3:
      for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
          if (right[i][j] == 1) {
            digitalWrite(x_axis[i], HIGH);
          } else {
            digitalWrite(x_axis[i], LOW);
          }
        }
        digitalWrite(y_axis[j], LOW);
        delayMicroseconds(350);
        digitalWrite(y_axis[j], HIGH);
      }
      break;
  };
}

void printArrow(int a)
{
  for (int k = 0; k < 150; k++) print_Matrix(a);
  for (int i = 0; i < 8; ++i) {
    digitalWrite(x_axis[i], LOW); //off
    digitalWrite(y_axis[i], HIGH); //off
  }
  delay(100);
}

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
