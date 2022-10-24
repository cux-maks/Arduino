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

int piezo = A13; // 스피커 핀 번호

int up_btn = 20; // + 버튼 핀 번호
int up_flag = 0; // + 버튼 플래그

int down_btn = 21; // - 버튼 핀 번호
int down_flag = 0; // - 버튼 플래그

int set_btn = 30; // set 버튼 핀 번호
int set_flag = 0; // set버튼 플래그

int h = 0; // 알람 시
int m = 0; // 알람 분
int s = 0; // 알람 초
int set_btn_state = 0; // set 버튼 상태

void switchFn(); // 이거 뭔지 모르는데 일단 필요한건 확실함

const byte segPin[8] = {3, 4, 5, 6, 7, 8, 9, 10}; //사용핀{a,b,c,d,e,f,g,dp} 순서대로임
const byte digitPin[6] = {A0, A1, A2, A3, A4, A5}; //segment 위치 핀
const byte interruptPin = 2;//인터럽트핀

boolean state = false;//시간 출력형식 지정
extern volatile unsigned long timer0_millis; //타이머변수
unsigned long readTime; //현재타이머시간
int hour_ = 0; // 현재 hour 입력 변수
int min_ = 0; // 현재 min 입력 변수
int sec_ = 0; // 현재 sec 입력 변수
int buf_t = 0; // 현재시간 설정 보정용 변수

int setTime(int time_, int term); // 시, 분, 초 값을 설정하는 함수 (코드 정리용)
void segPrint(int a, int b, int c); // 세그먼트 출력 함수 (코드 정리용)

void setup() {

  Serial.begin(9600); // 시리얼 시작

  pinMode(interruptPin, INPUT_PULLUP); // 12/24시간제 버튼 핀 INPUT_PULLUP으로 설정
  attachInterrupt(digitalPinToInterrupt(interruptPin), switchFn, FALLING); // 이거 뭔지 몰라

  for (int i = 0; i < 10; i++) { // 7-segment 각각 led 핀 output
    pinMode(segPin[i], OUTPUT);
  }
  for (int j = 0; j < 6; j++) { // 7-segment 각 자리 핀 output
    pinMode(digitPin[j], OUTPUT);
    digitalWrite(digitPin[j], HIGH);
  }

  pinMode(up_btn, INPUT_PULLUP); // + 버튼 INPUT_PULLUP으로 설정
  pinMode(down_btn, INPUT_PULLUP); // - 버튼 INPUT_PULLUP으로 설정
  pinMode(set_btn, INPUT_PULLUP); // set 버튼 INPUT_PULLUP으로 설정
  pinMode(piezo, OUTPUT); // 스피커 OUTPUT으로 설정

}

void loop() {

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
      else if (set_btn_state == 6) set_btn_state = 0;
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

    h = setTime(h, 10); // setTime함수로 h 값 설정
    h = h % 60;
    segPrint(h, m, s); // segPrint함수로 7-세그먼트에 출력

  } else if (set_btn_state == 4) { // 알람 m 설정

    m = setTime(m, 10); // setTime함수로 m 값 설정
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

    segPrint(hour_r, min_r, sec_r); // segPrint함수로 현재시간 출력

    up_flag = 0;
    down_flag = 0;

    checkTheAlarmTime(h, m, s, hour_r, min_r, sec_r); // 알람으로 설정한 시간과 현재 시간이 일치하는지 검사 및 일치하면 알람 울리기

  }

  if (state == true) { //12시 or 24시 출력모드
    hour_ = hour_ % 12;
  }

}

//12시 or 24시 출력 변경
void switchFn() {
  state = !state;
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
void checkTheAlarmTime(int h, int m, int s, int hour_r, int min_r, int sec_r) {
  if (h == hour_r && m == min_r && s == sec_r) {
    //analogWrite(piezo, 128);
    Serial.println("Alarm");
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
