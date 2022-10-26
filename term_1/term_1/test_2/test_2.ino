
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

int x_axis[] = {26, 27, 28, 29, 30, 31, 32, 33};
int y_axis[] = {34, 35, 36, 37, 38, 39, 40, 41};

int j = 0;

void setup() {
  for (int i = 0; i < 8; ++i) {
    pinMode(x_axis[i], OUTPUT);
    pinMode(y_axis[i], OUTPUT);
    digitalWrite(x_axis[i], LOW); //off
    digitalWrite(y_axis[i], HIGH); //off
  }
}

void loop() {
  // print_Matrix(0);

  print_Matrix(0);
  //
  //  print_Matrix(2);
  //
  //  print_Matrix(3);

}

void print_Matrix(int n) {

  digitalWrite(y_axis[j], HIGH);
  j++;
  if (j == 8) j = 0;

  switch (n) {
    case 0:
      for (int i = 0; i < 8; i++) {
        if (up[i][j] == 1) {
          digitalWrite(x_axis[i], HIGH);
        } else {
          digitalWrite(x_axis[i], LOW);
        }
      }
      digitalWrite(y_axis[j], LOW);
      break;
    case 1:
      for (int i = 0; i < 8; i++) {
        if (down[i][j] == 1) {
          digitalWrite(x_axis[i], HIGH);
        } else {
          digitalWrite(x_axis[i], LOW);
        }
      }
      digitalWrite(y_axis[j], LOW);
      break;
    case 2:
      for (int i = 0; i < 8; i++) {
        if (right[i][j] == 1) {
          digitalWrite(x_axis[i], HIGH);
        } else {
          digitalWrite(x_axis[i], LOW);
        }
      }
      digitalWrite(y_axis[j], LOW);
      break;
    case 3:
      for (int i = 0; i < 8; i++) {
        if (left[i][j] == 1) {
          digitalWrite(x_axis[i], HIGH);
        } else {
          digitalWrite(x_axis[i], LOW);
        }
      }
      digitalWrite(y_axis[j], LOW);
      break;
  };
}
