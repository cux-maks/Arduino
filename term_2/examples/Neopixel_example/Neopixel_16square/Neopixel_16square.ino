#include <Adafruit_NeoPixel.h>

#define CTRL_PIN 6 //제어 핀 번호
#define LED_CNT 256 //LED 개수
#define TERM 25

#define HEART_LIGHT strip.Color(32, 12, 24)
#define PULSE_LIGHT strip.Color(32, 16, 0)

const unsigned int haert_img[5][16] = 
{
  {0x0000,  0x0000,  0x0000,  0x01E0,  0x03F0,  0x07F8,  0x0FF0,  0x1FE0,  0x1FE0,  0x0FF0,  0x07F8,  0x03F0,  0x01E0,  0x0000,  0x0000,  0x0000},
  {0x0000,  0x00F0,  0x03FC,  0x07FE,  0x0FFE,  0x1FFE,  0x3FFC,  0x7FF8,  0x7FF8,  0x3FFC,  0x1FFE,  0x0FFE,  0x07FE,  0x03FC,  0x00F0,  0x0000},
  {0x0000,  0x0000,  0x01F0,  0x03F8,  0x07FC,  0x0FFC,  0x1FF8,  0x3FF0,  0x3FF0,  0x1FF8,  0x0FFC,  0x07FC,  0x03F8,  0x01F0,  0x0000,  0x0000},
  {0x0000,  0x0000,  0x00E0,  0x01F8,  0x03FC,  0x07FC,  0x0FF8,  0x1FF0,  0x1FF0,  0x0FF8,  0x07FC,  0x03FC,  0x01F8,  0x00E0,  0x0000,  0x0000},
  {0x0000,  0x0000,  0x0000,  0x01E0,  0x03F0,  0x07F8,  0x0FF0,  0x1FE0,  0x1FE0,  0x0FF0,  0x07F8,  0x03F0,  0x01E0,  0x0000,  0x0000,  0x0000}
},
pulse_img[5][16] =
{
  {0x0100,  0x0100,  0x0100,  0x00E0,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000},
  {0x0100,  0x0100,  0x0100,  0x00E0,  0x001C,  0x00E0,  0x0300,  0x0C00,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000},
  {0x0000,  0x0000,  0x0000,  0x0000,  0x001C,  0x00E0,  0x0300,  0x0C00,  0x0300,  0x00C0,  0x0300,  0x0180,  0x0000,  0x0000,  0x0000,  0x0000},
  {0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0300,  0x00C0,  0x0300,  0x0180,  0x0200,  0x0100,  0x0100,  0x0100},
  {0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0000,  0x0200,  0x0100,  0x0100,  0x0100}
};

unsigned int mtrx_add[16][16] = {0,};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_CNT, CTRL_PIN, NEO_GRB + NEO_KHZ800); // 객체 선언

void setup()
{
  unsigned l=0, sum_flag = 0, sum_num = 31;
  
  strip.begin(); // LED 초기화
  strip.show(); // 초기화를 위한 LED 소등

  for(unsigned int m = 0; m < 16; m++)
  {
    l = m;
    for(unsigned int n = 0; n < 16; n++)
    {
      mtrx_add[15-m][n] = l;
      if(sum_flag == 0)
      {
        l += sum_num;
        sum_flag++;
      }
      else 
      {
        l += 32-sum_num;
        sum_flag = 0;
      }
    }
    sum_num -= 2;
  }
}

void loop()
{
  heartbeat_led();
}

void heartbeat_led()
{
  for(unsigned int m = 0; m<5; m++)
  {
    if(m>0)
    {
      for(unsigned int n = (m-1)*4; n<16; n++)
      {
        for(unsigned int l = 0; l<16; l++)
        {
          if(pulse_img[m-1][n]>>l & 0x0001)
          {
            strip.setPixelColor(mtrx_add[n][l],PULSE_LIGHT);
          }
        }
      }
    }
    for(unsigned int n = m*4; n<16; n++)
    {
      for(unsigned int l = 0; l<16; l++)
      {
        if(pulse_img[m][n]>>l & 0x0001)
        {
          strip.setPixelColor(mtrx_add[n][l],PULSE_LIGHT);
          strip.show();
          delay(20);
        }
      }
    }
    for(unsigned int n = 0; n<16; n++)
    {
      for(unsigned int l = 0; l<16; l++)
      {
        if(haert_img[m][n]>>l & 0x0001)
        {
          strip.setPixelColor(mtrx_add[n][l],HEART_LIGHT);
        }
        else
        {
          strip.setPixelColor(mtrx_add[n][l],0);
        }
      }
    }
  }
}
