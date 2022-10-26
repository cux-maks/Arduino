#include <FrequencyTimer2.h>

//up
#define up{\
{0,0,0,1,1,0,0,0},\
{0,0,1,1,1,1,0,0},\
{0,1,1,1,1,1,1,0},\
{1,1,1,1,1,1,1,1},\
{0,0,1,1,1,1,0,0},\
{0,0,1,1,1,1,0,0},\
{0,0,1,1,1,1,0,0},\
{0,0,1,1,1,1,0,0} \
}

//down
#define down{\
{0,0,1,1,1,1,0,0},\
{0,0,1,1,1,1,0,0},\
{0,0,1,1,1,1,0,0},\
{0,0,1,1,1,1,0,0},\
{1,1,1,1,1,1,1,1},\
{0,1,1,1,1,1,1,0},\
{0,0,1,1,1,1,0,0},\
{0,0,0,1,1,0,0,0} \
}

//right
#define right{\
{0,0,0,0,1,0,0,0},\
{0,0,0,0,1,1,0,0},\
{1,1,1,1,1,1,1,0},\
{1,1,1,1,1,1,1,1},\
{1,1,1,1,1,1,1,1},\
{1,1,1,1,1,1,1,0},\
{0,0,0,0,1,1,0,0},\
{0,0,0,0,1,0,0,0} \
}

//left
#define left{\
{0,0,0,1,0,0,0,0},\
{0,0,1,1,0,0,0,0},\
{0,1,1,1,1,1,1,1},\
{1,1,1,1,1,1,1,1},\
{1,1,1,1,1,1,1,1},\
{0,1,1,1,1,1,1,1},\
{0,0,1,1,0,0,0,0},\
{0,0,0,1,0,0,0,0} \
}

int push_btn = 8; //pin again
byte col = 0;
byte leds[8][8];

int pins[17]= {-1, 5, 4, 3, 2, 14, 15, 16, 17, 13, 12, 11, 10, 9,8, 7, 6}; 
// col[xx] of leds = pin yy on led matrixint 
cols[8] = {pins[13], pins[3], pins[4], pins[10], pins[06],pins[11], pins[15], pins[16]}; 
// row[xx] of leds = pin yy on led matrixint 
rows[8] = {pins[9], pins[14], pins[8], pins[12], pins[1],pins[7], pins[2], pins[5]};

const int arrPatterns = 4;
byte patterns[arrPatterns][8][8] = {
  up, down, right, left};

int pattern = 0;

void setup(){
  for(int i = 1; i<=16; i++){
    pinMode(pin[i], OUTPUT);
  }

  for(int i=0; i<8; i++){
    digitalWrite(cols[i], HIGH);
  }

  for(int i=0; i<8; i++){
    digitalWrite(rows[i], HIGH);
  }

  clearLed();

  FrequencyTimer2::setOnOverflow(display);

  pinMode(push_btn, INPUT);

  setPattern(pattern);
}

void loop(){
  //pinMode(버튼핀, INPUT_PULLUP);

// 플래그 적용
  //if(digitalRead(버튼핀) == 0){
    //if(flag == 0){
      //flag = 1;
    //  여기에 할 작업 입력
    //}else{}
  //}else{
    //flag = 0;
  //}
  
  int readpush_btn = digital(push_btn);

  int randnum = rand(5,15);
  
  if(readpush_btn == HIGH){
    while(randnum>0){
      pattern = rand(0,4);
      setPattern(pattern);
      randnum--;
    }
  }
  setPattern(pattern);
}

void clearLeds(){
  for(int i=0; i<8; i++)
    for(int j=0; j<8; j++)
      leds[i][j]=0;
}

void setPattern(int pattern){
  for(int i=0; i<8; i++)
    for(int j=0; j<8; j++)
      leds[i][j] = patterns[pattern][i][j];
}

void display(){
  digitalWrite(cols[col], HIGH);
  col++;
  if(col==8){
    col=0;
  }
  for(int row=0; row<=7; row++){
    if(leds[col][7-row]==1){
      digitalWrite(rows[row], HIGH);
    }
    else{
      digitalWrite(rows[row], LOW);
    }
  }
  digitalWrite(cols[col], LOW);
}
  
