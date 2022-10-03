int up_btn = 8;
int up_flag = 0;

int down_btn = 7;
int down_flag = 0;

int set_btn = 13;
int set_flag = 0;

int h = 0;
int m = 0;
int state = 0;

void setup() {

  pinMode(up_btn, INPUT_PULLUP);
  pinMode(down_btn, INPUT_PULLUP);
  pinMode(set_btn, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {

  if (digitalRead(set_btn) == 0){
    if(set_flag == 0){
      if(state == 0) state = 1;
      else if(state == 1) state = 2;
      else state = 0;
      set_flag = 1;
    }else{}
  }else{
    set_flag = 0;
  }

  if(state == 0){
    if(digitalRead(up_btn) == 0){
      if(up_flag == 0){
        up_flag = 1;
        h++;
      }else{}
    }else if(digitalRead(down_btn) == 0){
      if(down_flag == 0){
        down_flag = 1;
        h--;
      }else{}
    }else{
      up_flag = 0;
      down_flag = 0;
    }
  }else if(state == 1){
   if(digitalRead(up_btn) == 0){
      if(up_flag == 0){
        up_flag = 1;
        m++;
      }else{}
    }else if(digitalRead(down_btn) == 0){
      if(down_flag == 0){
        down_flag = 1;
        m--;
      }else{}
    }else{
      up_flag = 0;
      down_flag = 0;
    }
  }

  if(m >= 60){
    h += 1;
    m = 0;
  }else if(m < 0){
    m = 0;
  }

  if(h >= 24 || h < 0){
    h = 0;
  }

  Serial.print("h: ");
  Serial.print(h);
  Serial.print(" m: ");
  Serial.print(m);
  Serial.print(" state: ");
  Serial.println(state);

}
