#include <Adafruit_NeoPixel.h>

#define CTRL_PIN 7 //제어 핀 번호
#define LED_CNT 72 //LED 개수
#define TERM "41"
// #define TERM 3000/LED_CNT

#define RED_LIGHT strip.Color(32, 0, 0)
#define GREEN_LIGHT strip.Color(0, 32, 0)
#define BLUE_LIGHT strip.Color(0, 0, 32)
#define PINK_LIGHT strip.Color(32, 12, 24)

#define YELLO_LIGHT strip.Color(32, 32, 0)
#define CYAN_LIGHT strip.Color(0, 32, 32)
#define MAGENTA_LIGHT strip.Color(32, 0, 32)

#define WHITE_LIGHT strip.Color(32, 32, 32)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_CNT, CTRL_PIN, NEO_GRB + NEO_KHZ800); // 객체 선언

void setup()
{
  strip.begin(); // LED 초기화
  strip.show(); // 초기화를 위한 LED 소등
  
  Serial.begin(9600); // 시리얼 통신 초기화
  while (!Serial); // 시리얼 통신응답 대기
  Serial.println("Booting Success");
}

String led_cmd = "";
unsigned char turn_cnt = 0;

void loop()
{
  char cmd_char = 0;
  char op_flag = 0;
  
  if (Serial.available())
  {
    cmd_char = Serial.read();
    Serial.write(cmd_char);
    led_cmd.concat(cmd_char);
    if(cmd_char == 0x5C) //명령 실패시 탈출 명령어 '\'
    {
      led_cmd = "";
      Serial.println();
    }
  }
  op_flag = Neopixel_ctrl(led_cmd);
  if(op_flag == 1) led_cmd = "";
}

boolean Neopixel_ctrl(String ctrl)
{
  if(ctrl == "red")
  {
    stack_led(RED_LIGHT, TERM); //빨간색 출력
    Serial.println("test");
    return 1;
  }
  else if(ctrl == "green")
  {
    stack_led(GREEN_LIGHT, TERM); //녹색 출력
    Serial.println();
    return 1;
  }
  else if(ctrl == "blue")
  {
    stack_led(BLUE_LIGHT, TERM); //파랑색 출력
    Serial.println();
    return 1;
  }
  else if(ctrl == "pink")
  {
    stack_led(PINK_LIGHT, TERM); //분홍색 출력
    Serial.println();
    return 1;
  }
  else if(ctrl == "white")
  {
    stack_led(WHITE_LIGHT, TERM); //흰색 출력
    Serial.println();
    return 1;
  }
  else if(ctrl == "epic")
  {
    epic_led(TERM);
    Serial.println();
    return 1;
  }
  else if(ctrl == "on")
  {
      turn_on();
      Serial.println();
      return 1;
  }
  else if(ctrl == "off")
  {
      turn_off();
      Serial.println();
      return 1;
  }
  else
  {
    return 0;
  }
}

void stack_led(unsigned int c, unsigned char wait)
{
  for(uint16_t i=0; i<strip.numPixels(); i++)
  {
      strip.setPixelColor(i, c);
      strip.show();
      Serial.println("test_2");
      delay(wait);
  }
  turn_off();
}


void turn_on() // LED 점등
{
  for(unsigned int i=0; i<strip.numPixels(); i++)
  {
      strip.setPixelColor(i, WHITE_LIGHT);
  }
  strip.show();
}

void turn_off() // LED 소등
{
  for(unsigned int i=0; i<strip.numPixels(); i++)
  {
      strip.setPixelColor(i, 0);
  }
  strip.show();
}


void epic_led(unsigned char wait)
{
  uint16_t i, j=5;

  for(uint16_t i=0; i<strip.numPixels()+j*7; i++)
  {
      strip.setPixelColor(i, 0xff0000);
      if(i >= j*1) strip.setPixelColor(i-j*1, MAGENTA_LIGHT);
      if(i >= j*2) strip.setPixelColor(i-j*2, BLUE_LIGHT);
      if(i >= j*3) strip.setPixelColor(i-j*3, CYAN_LIGHT);
      if(i >= j*4) strip.setPixelColor(i-j*4, GREEN_LIGHT);
      if(i >= j*5) strip.setPixelColor(i-j*5, YELLO_LIGHT);
      if(i >= j*6) strip.setPixelColor(i-j*6, PINK_LIGHT);
      if(i >= j*7) strip.setPixelColor(i-j*7, WHITE_LIGHT);
      strip.show();
      delay(wait);
  }
  turn_off();
}
