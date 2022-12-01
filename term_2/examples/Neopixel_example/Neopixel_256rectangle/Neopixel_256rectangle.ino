#include <Adafruit_NeoPixel.h>

#define CTRL_PIN 6 //제어 핀 번호
#define LED_CNT 256 //LED 개수
#define TERM 50 //사용할 딜레이

#define RED_LIGHT strip.Color(32, 0, 0)
#define GREEN_LIGHT strip.Color(0, 32, 0)
#define BLUE_LIGHT strip.Color(0, 0, 32)
#define PINK_LIGHT strip.Color(32, 16, 24)
#define WHITE_LIGHT strip.Color(32, 32, 32)

#define YELLO_LIGHT strip.Color(32, 32, 0)
#define CYAN_LIGHT strip.Color(0, 32, 32)
#define MAGENTA_LIGHT strip.Color(32, 0, 32)

const unsigned int
text_A[8]   = {0x00,  0x7C,  0x12,  0x11,  0x12,  0x7C,  0xFF,  0xFF},
text_B[8]   = {0x00,  0x7F,  0x49,  0x49,  0x49,  0x36,  0xFF,  0xFF},
text_C[8]   = {0x00,  0x3E,  0x41,  0x41,  0x41,  0x22,  0xFF,  0xFF},
text_D[8]   = {0x00,  0x7F,  0x41,  0x41,  0x41,  0x3E,  0xFF,  0xFF},
text_E[8]   = {0x00,  0x7F,  0x49,  0x49,  0x49,  0x41,  0xFF,  0xFF},
text_F[8]   = {0x00,  0x7F,  0x09,  0x09,  0x09,  0x01,  0xFF,  0xFF},
text_G[8]   = {0x00,  0x3E,  0x41,  0x41,  0x29,  0x7A,  0xFF,  0xFF},
text_H[8]   = {0x00,  0x7F,  0x08,  0x08,  0x08,  0x7F,  0xFF,  0xFF},
text_I[8]   = {0x00,  0x41,  0x7F,  0x41,  0xFF,  0xFF,  0xFF,  0xFF},
text_J[8]   = {0x00,  0x20,  0x40,  0x41,  0x3F,  0x01,  0xFF,  0xFF},
text_K[8]   = {0x00,  0x7F,  0x08,  0x08,  0x14,  0x63,  0xFF,  0xFF},
text_L[8]   = {0x00,  0x7F,  0x40,  0x40,  0x40,  0x40,  0xFF,  0xFF},
text_M[8]   = {0x00,  0x7F,  0x06,  0x18,  0x06,  0x7F,  0xFF,  0xFF},
text_N[8]   = {0x00,  0x7F,  0x04,  0x08,  0x10,  0x7F,  0xFF,  0xFF},
text_O[8]   = {0x00,  0x3E,  0x41,  0x41,  0x41,  0x3E,  0xFF,  0xFF},
text_P[8]   = {0x00,  0x7F,  0x09,  0x09,  0x09,  0x06,  0xFF,  0xFF},
text_Q[8]   = {0x00,  0x3E,  0x41,  0x41,  0x41,  0xBE,  0xFF,  0xFF},
text_R[8]   = {0x00,  0x7F,  0x09,  0x09,  0x09,  0x76,  0xFF,  0xFF},
text_S[8]   = {0x00,  0x26,  0x49,  0x49,  0x49,  0x32,  0xFF,  0xFF},
text_T[8]   = {0x00,  0x01,  0x01,  0x7F,  0x01,  0x01,  0xFF,  0xFF},
text_U[8]   = {0x00,  0x3F,  0x40,  0x40,  0x40,  0x3F,  0xFF,  0xFF},
text_V[8]   = {0x00,  0x07,  0x18,  0x60,  0x18,  0x07,  0xFF,  0xFF},
text_W[8]   = {0x00,  0x7F,  0x30,  0x0C,  0x30,  0x7F,  0xFF,  0xFF},
text_X[8]   = {0x00,  0x63,  0x14,  0x08,  0x14,  0x63,  0xFF,  0xFF},
text_Y[8]   = {0x00,  0x03,  0x04,  0x78,  0x04,  0x03,  0xFF,  0xFF},
text_Z[8]   = {0x00,  0x61,  0x51,  0x49,  0x45,  0x43,  0xFF,  0xFF},
text_at[8]  = {0x00,  0x1C,  0x22,  0x59,  0x55,  0x4D,  0x51,  0x0E},
text_a[8]   = {0x00,  0x20,  0x54,  0x54,  0x78,  0xFF,  0xFF,  0xFF},
text_b[8]   = {0x00,  0x7E,  0x50,  0x48,  0x30,  0xFF,  0xFF,  0xFF},
text_c[8]   = {0x00,  0x38,  0x44,  0x44,  0x28,  0xFF,  0xFF,  0xFF},
text_d[8]   = {0x00,  0x30,  0x48,  0x28,  0x7E,  0xFF,  0xFF,  0xFF},
text_e[8]   = {0x00,  0x38,  0x54,  0x54,  0x48,  0xFF,  0xFF,  0xFF},
text_f[8]   = {0x00,  0x04,  0x7E,  0x05,  0xFF,  0xFF,  0xFF,  0xFF},
text_g[8]   = {0x00,  0x18,  0xA4,  0x94,  0x7E,  0xFF,  0xFF,  0xFF},
text_h[8]   = {0x00,  0x7E,  0x10,  0x08,  0x70,  0xFF,  0xFF,  0xFF},
text_i[8]   = {0x00,  0x7A,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF},
text_j[8]   = {0x00,  0x80,  0x7A,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF},
text_k[8]   = {0x00,  0x7E,  0x10,  0x28,  0x44,  0xFF,  0xFF,  0xFF},
text_l[8]   = {0x00,  0x7E,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF},
text_m[8]   = {0x00,  0x7C,  0x04,  0x78,  0x04,  0x78,  0xFF,  0xFF},
text_n[8]   = {0x00,  0x7C,  0x04,  0x04,  0x04,  0x78,  0xFF,  0xFF},
text_o[8]   = {0x00,  0x38,  0x44,  0x44,  0x38,  0xFF,  0xFF,  0xFF},
text_p[8]   = {0x00,  0xFC,  0x14,  0x24,  0x18,  0xFF,  0xFF,  0xFF},
text_q[8]   = {0x00,  0x18,  0x24,  0x14,  0xFC,  0xFF,  0xFF,  0xFF},
text_r[8]   = {0x00,  0x7C,  0x08,  0x04,  0xFF,  0xFF,  0xFF,  0xFF},
text_s[8]   = {0x00,  0x48,  0x54,  0x54,  0x24,  0xFF,  0xFF,  0xFF},
text_t[8]   = {0x00,  0x04,  0x7E,  0x04,  0xFF,  0xFF,  0xFF,  0xFF},
text_u[8]   = {0x00,  0x3C,  0x40,  0x40,  0x7C,  0xFF,  0xFF,  0xFF},
text_v[8]   = {0x00,  0x1C,  0x20,  0x40,  0x20,  0x1C,  0xFF,  0xFF},
text_w[8]   = {0x00,  0x3C,  0x40,  0x3C,  0x40,  0x3C,  0xFF,  0xFF},
text_x[8]   = {0x00,  0x44,  0x28,  0x10,  0x28,  0x44,  0xFF,  0xFF},
text_y[8]   = {0x00,  0x1C,  0xA0,  0xA0,  0xA0,  0x3C,  0xFF,  0xFF},
text_z[8]   = {0x00,  0x44,  0x64,  0x54,  0x4C,  0x44,  0xFF,  0xFF},
text_dot[8] = {0x00,  0x40,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF,  0xFF},
text_0[8]   = {0x00,  0x3E,  0x51,  0x49,  0x45,  0x3E,  0xFF,  0xFF},
text_1[8]   = {0x00,  0x42,  0x7F,  0x40,  0xFF,  0xFF,  0xFF,  0xFF},
text_2[8]   = {0x00,  0x62,  0x51,  0x49,  0x49,  0x46,  0xFF,  0xFF},
text_3[8]   = {0x00,  0x22,  0x49,  0x49,  0x49,  0x36,  0xFF,  0xFF},
text_4[8]   = {0x00,  0x18,  0x14,  0x12,  0x7F,  0x10,  0xFF,  0xFF},
text_5[8]   = {0x00,  0x27,  0x45,  0x45,  0x45,  0x39,  0xFF,  0xFF},
text_6[8]   = {0x00,  0x3E,  0x49,  0x49,  0x49,  0x32,  0xFF,  0xFF},
text_7[8]   = {0x00,  0x03,  0x01,  0x71,  0x0D,  0x03,  0xFF,  0xFF},
text_8[8]   = {0x00,  0x36,  0x49,  0x49,  0x49,  0x36,  0xFF,  0xFF},
text_9[8]   = {0x00,  0x26,  0x49,  0x49,  0x49,  0x3E,  0xFF,  0xFF};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_CNT, CTRL_PIN, NEO_GRB + NEO_KHZ800); // 객체 선언

unsigned int mtrx_add[8][32] = {0,};

void setup()
{
  unsigned int l=0, sum_flag = 0, sum_num = 15;
  
  strip.begin(); // LED 초기화
  strip.show(); // 초기화를 위한 LED 소등
  
  Serial.begin(9600); // 시리얼 통신 초기화
  while (!Serial); // 시리얼 통신응답 대기

  for(unsigned int m = 0; m < 8; m++)
  {
    l = m;
    for(unsigned int n = 0; n < 32; n++)
    {
      mtrx_add[m][n] = l;
      if(sum_flag == 0)
      {
        l += sum_num;
        sum_flag++;
      }
      else 
      {
        l += 16-sum_num;
        sum_flag = 0;
      }
    }
    sum_num -= 2;
  }
  
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
    if(cmd_char == 0x5C)
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
  if(ctrl == "on")
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
  else if(ctrl == "text")
  {
    Serial.println();
    text_mode();
    return 1;
  }
  else
  {
    return 0;
  }
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

void text_mode()
{
  turn_off();
  unsigned char text_cursor = 0, char_num = 0;
  Serial.println("text output");
  
  for(unsigned int m=0; m<32; m++)
  {
    for(unsigned int n=0; n<8; n++)
    {
      if(char_num == 0)
      {
        if(((text_D[text_cursor]==0xff) || (text_cursor%8==7)))
        {
          char_num++;
          text_cursor=0;
        }
        if((text_D[text_cursor]!=0xff) && (text_D[text_cursor]>>n & 0x01))
        {
          strip.setPixelColor(mtrx_add[n][m],strip.Color(0, 32-(text_cursor*4), (32-text_cursor*4)));
        }
      }
      if(char_num == 1)
      {
        if(((text_e[text_cursor]==0xff) || (text_cursor%8==7)))
        {
          char_num++;
          text_cursor=0;
        }
        if((text_e[text_cursor]!=0xff) && (text_e[text_cursor]>>n & 0x01))
        {
          strip.setPixelColor(mtrx_add[n][m],strip.Color(32-(text_cursor*4), 0, (32-text_cursor*4)));
        }
      }
      if(char_num == 2)
      {
        if(((text_v[text_cursor]==0xff) || (text_cursor%8==7)))
        {
          char_num++;
          text_cursor=0;
        }
        if((text_v[text_cursor]!=0xff) && (text_v[text_cursor]>>n & 0x01))
        {
          strip.setPixelColor(mtrx_add[n][m],strip.Color(32-(text_cursor*4), 32-(text_cursor*4), 0));
        }
      }
      if(char_num == 3)
      {
        if(((text_i[text_cursor]==0xff) || (text_cursor%8==7)))
        {
          char_num++;
          text_cursor=0;
        }
        if((text_i[text_cursor]!=0xff) && (text_i[text_cursor]>>n & 0x01))
        {
          strip.setPixelColor(mtrx_add[n][m],strip.Color(16-(text_cursor*2), 32-(text_cursor*4), 16-(text_cursor*2)));
        }
      }
      if(char_num == 4)
      {
        if(((text_c[text_cursor]==0xff) || (text_cursor%8==7)))
        {
          char_num++;
          text_cursor=0;
        }
        if((text_c[text_cursor]!=0xff) && (text_c[text_cursor]>>n & 0x01))
        {
          strip.setPixelColor(mtrx_add[n][m],strip.Color(32-(text_cursor*4), 16-(text_cursor*2), 16-(text_cursor*2)));
        }
      }
      if(char_num == 5)
      {
        if(((text_e[text_cursor]==0xff) || (text_cursor%8==7)))
        {
          char_num++;
          text_cursor=0;
        }
        if((text_e[text_cursor]!=0xff) && (text_e[text_cursor]>>n & 0x01))
        {
          strip.setPixelColor(mtrx_add[n][m],strip.Color(16-(text_cursor*2), 16-(text_cursor*2), 32-(text_cursor*4)));
        }
      }
      if(text_cursor == 0) delay(TERM);
    }
    text_cursor++;
    strip.show();
  }
  turn_off();
  text_cursor = 0;
  char_num = 0;
  for(unsigned int m=0; m<32; m++)
  {
    for(unsigned int n=0; n<8; n++)
    {
      if(char_num == 0)
      {
        if(((text_m[text_cursor]==0xff) || (text_cursor%8==7)))
        {
          char_num++;
          text_cursor=0;
        }
        if((text_m[text_cursor]!=0xff) && (text_m[text_cursor]>>n & 0x01))
        {
          strip.setPixelColor(mtrx_add[n][m],strip.Color(0, 32-(text_cursor*4), (32-text_cursor*4)));
        }
      }
      if(char_num == 1)
      {
        if(((text_a[text_cursor]==0xff) || (text_cursor%8==7)))
        {
          char_num++;
          text_cursor=0;
        }
        if((text_a[text_cursor]!=0xff) && (text_a[text_cursor]>>n & 0x01))
        {
          strip.setPixelColor(mtrx_add[n][m],strip.Color(32-(text_cursor*4), 0, (32-text_cursor*4)));
        }
      }
      if(char_num == 2)
      {
        if(((text_r[text_cursor]==0xff) || (text_cursor%8==7)))
        {
          char_num++;
          text_cursor=0;
        }
        if((text_r[text_cursor]!=0xff) && (text_r[text_cursor]>>n & 0x01))
        {
          strip.setPixelColor(mtrx_add[n][m],strip.Color(32-(text_cursor*4), 32-(text_cursor*4), 0));
        }
      }
      if(char_num == 3)
      {
        if(((text_t[text_cursor]==0xff) || (text_cursor%8==7)))
        {
          char_num++;
          text_cursor=0;
        }
        if((text_t[text_cursor]!=0xff) && (text_t[text_cursor]>>n & 0x01))
        {
          strip.setPixelColor(mtrx_add[n][m],strip.Color(16-(text_cursor*2), 32-(text_cursor*4), 16-(text_cursor*2)));
        }
      }
      if(text_cursor == 0) delay(TERM);
    }
    text_cursor++;
    strip.show();
  }
}
