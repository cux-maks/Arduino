int led = 11;

void setup() {
  pinMode(led, OUTPUT);
}

void loop() {

  for(int i = 0; i < 255; i++){
    analogWrite(led, i);
    delay(2);
  }
  for(int i = 255; i > 0; i--){
    analogWrite(led, i);
    delay(2);
  }

}
