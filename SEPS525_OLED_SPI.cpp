#include <SEPS525_OLED_SPI.h>

static inline void seps525_datastart(void)
{
  // digitalWrite(pinSS, LOW);
  // digitalWrite(pinRS, LOW);
  // SPI.transfer(0x22);
  // digitalWrite(pinRS, HIGH);
}

static inline void seps525_data(int value)
{
  // SPI.transfer((value>>8)& 0xFF);
  // SPI.transfer(value & 0xFF);
}

static inline void seps525_dataend(void)
{
  // digitalWrite(pinSS, HIGH);
}

static void seps525_set_region(int x, int y, int xs, int ys)
{
  // // draw region
  // seps525_reg(0x17,x);
  // seps525_reg(0x18,x+xs-1);
  // seps525_reg(0x19,y);
  // seps525_reg(0x1a,y+ys-1);
  
  // // start position
  // seps525_reg(0x20,x);
  // seps525_reg(0x21,y);
}

void SEPS525_OLED::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  seps525_set_region(x, y, 1, 1);
  seps525_datastart();
  seps525_data(color);
  seps525_dataend();
}

void SEPS525_OLED::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
  seps525_set_region(x, y, 1, h);
  seps525_datastart();
  int n;
  for(n = 0; n < h; n++) seps525_data(color);
  seps525_dataend();
}

void SEPS525_OLED::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
  seps525_set_region(x, y, w, 1);
  seps525_datastart();
  int n;
  for(n = 0; n < w; n++) seps525_data(color);
  seps525_dataend();
}

void SEPS525_OLED::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  seps525_set_region(x, y, w, h);
  seps525_datastart();
  int n;
  for(n = 0; n < h*w; n++) seps525_data(color);
  seps525_dataend();
}

uint16_t SEPS525_OLED::color565(uint8_t r, uint8_t g, uint8_t b)
{
  return (r << 11) | (g << 5) | b;
}


SEPS525_OLED::SEPS525_OLED(int8_t SDI_PIN, int8_t SCL_PIN, int8_t RS_PIN, int8_t RES_PIN, int8_t CS_PIN) : Adafruit_GFX(160, 128) 
{
  sdi_pin = SDI_PIN;
  scl_pin = SCL_PIN;
  rs_pin = RS_PIN;
  res_pin = RES_PIN;
  cs_pin = CS_PIN;
}

void SEPS525_OLED::begin(){

  DDRD = 0xFF;                                    // configure PORTD as output
  pinMode(rs_pin, OUTPUT);                        // configure rs_pin as output
  pinMode(res_pin, OUTPUT);                       // configure res_pin as output
  pinMode(cs_pin, OUTPUT);                        // configure cs_pin as output
  digitalWrite(cs_pin, HIGH);                     // set cs_pin

  pinMode(sdi_pin, OUTPUT);                   // configure sdi_pin as output
  pinMode(scl_pin, OUTPUT);                   // configure scl_pin as output
  PORTD = 0x00;                               // reset sdi_pin and scl_pin, ground DB[5..0] of the display

}


void SEPS525_OLED::OLED_Init_160128RGB(void)      //OLED initialization
{
    digitalWrite(res_pin, LOW);
    delay(500);
    digitalWrite(res_pin, HIGH);
    delay(500);

    OLED_Command_160128RGB(0x04);// Set Normal Driving Current
    OLED_Data_160128RGB(0x03);// Disable Oscillator Power Down
    delay(2);
    OLED_Command_160128RGB(0x04); // Enable Power Save Mode
    OLED_Data_160128RGB(0x00); // Set Normal Driving Current
    delay(2); // Disable Oscillator Power Down
    OLED_Command_160128RGB(0x3B);
    OLED_Data_160128RGB(0x00);
    OLED_Command_160128RGB(0x02);
    OLED_Data_160128RGB(0x01); // Set EXPORT1 Pin at Internal Clock
    // Oscillator operates with external resister.
    // Internal Oscillator On
    OLED_Command_160128RGB(0x03);
    OLED_Data_160128RGB(0x90); // Set Clock as 90 Frames/Sec
    OLED_Command_160128RGB(0x80);
    OLED_Data_160128RGB(0x01); // Set Reference Voltage Controlled by External Resister
    OLED_Command_160128RGB(0x08);// Set Pre-Charge Time of Red
    OLED_Data_160128RGB(0x04);
    OLED_Command_160128RGB(0x09);// Set Pre-Charge Time of Green
    OLED_Data_160128RGB(0x05);
    OLED_Command_160128RGB(0x0A);// Set Pre-Charge Time of Blue
    OLED_Data_160128RGB(0x05);
    OLED_Command_160128RGB(0x0B);// Set Pre-Charge Current of Red
    OLED_Data_160128RGB(0x9D);
    OLED_Command_160128RGB(0x0C);// Set Pre-Charge Current of Green
    OLED_Data_160128RGB(0x8C);
    OLED_Command_160128RGB(0x0D);// Set Pre-Charge Current of Blue
    OLED_Data_160128RGB(0x57);
    OLED_Command_160128RGB(0x10);// Set Driving Current of Red
    OLED_Data_160128RGB(0x56);
    OLED_Command_160128RGB(0x11);// Set Driving Current of Green
    OLED_Data_160128RGB(0x4D);
    OLED_Command_160128RGB(0x12);// Set Driving Current of Blue
    OLED_Data_160128RGB(0x46);
    OLED_Command_160128RGB(0x13);
    OLED_Data_160128RGB(0xA0); // Set Color Sequence
    OLED_Command_160128RGB(0x14);
    OLED_Data_160128RGB(0x01); // Set MCU Interface Mode
    OLED_Command_160128RGB(0x16);
    OLED_Data_160128RGB(0x76); // Set Memory Write Mode
    OLED_Command_160128RGB(0x28);
    OLED_Data_160128RGB(0x7F); // 1/128 Duty (0x0F~0x7F)
    OLED_Command_160128RGB(0x29);
    OLED_Data_160128RGB(0x00); // Set Mapping RAM Display Start Line (0x00~0x7F)
    OLED_Command_160128RGB(0x06);
    OLED_Data_160128RGB(0x01); // Display On (0x00/0x01)
    OLED_Command_160128RGB(0x05); // Disable Power Save Mode
    OLED_Data_160128RGB(0x00); // Set All Internal Register Value as Normal Mode
    OLED_Command_160128RGB(0x15);
    OLED_Data_160128RGB(0x00); // Set RGB Interface Polarity as Active Low
    OLED_SetColumnAddress_160128RGB(0, 159);
    OLED_SetRowAddress_160128RGB(0, 127);
}
void SEPS525_OLED::OLED_Command_160128RGB(unsigned char c)        // send command to OLED
{  
  unsigned char i;
  unsigned char mask = 0x80;
   
  digitalWrite(cs_pin, LOW);               
  digitalWrite(rs_pin, LOW);
  for(i=0;i<8;i++)
  {
     digitalWrite(scl_pin, LOW);
     if((c & mask) >> 7 == 1)
     {
        digitalWrite(sdi_pin, HIGH);
     }
     else
     {
        digitalWrite(sdi_pin, LOW);
     }
     digitalWrite(scl_pin, HIGH);
     c = c << 1;
  }
  digitalWrite(cs_pin, HIGH);
} 

void SEPS525_OLED::OLED_Data_160128RGB(unsigned char d)        // send data to OLED
{ 
  unsigned char i;
  unsigned char mask = 0x80;
   
  digitalWrite(cs_pin, LOW);               
  digitalWrite(rs_pin, HIGH);
  for(i=0;i<8;i++)
  {
     digitalWrite(scl_pin, LOW);
     if((d & mask) >> 7 == 1)
     {
        digitalWrite(sdi_pin, HIGH);
     }
     else
     {
        digitalWrite(sdi_pin, LOW);
     }
     digitalWrite(scl_pin, HIGH);
     d = d << 1;
  }
  digitalWrite(cs_pin, HIGH);
}

void SEPS525_OLED::OLED_SerialPixelData_160128RGB(unsigned char d)    // serial write for pixel data
{
   unsigned char i;
   unsigned char mask = 0x80;
   digitalWrite(cs_pin, LOW);               
   digitalWrite(rs_pin, HIGH);
   for(i=0;i<6;i++)
   {
     digitalWrite(scl_pin, LOW);
     if((d & mask) >> 7 == 1)
     {
       digitalWrite(sdi_pin, HIGH);
     }
     else
     {
       digitalWrite(sdi_pin, LOW);
     }
     digitalWrite(scl_pin, HIGH);
     d = d << 1;
   }
   digitalWrite(cs_pin, HIGH);
}
  
void SEPS525_OLED::OLED_SetColumnAddress_160128RGB(unsigned char x_start, unsigned char x_end)    // set column address start + end
{
    OLED_Command_160128RGB(0x17);
    OLED_Data_160128RGB(x_start);
    OLED_Command_160128RGB(0x18);
    OLED_Data_160128RGB(x_end);
}

void SEPS525_OLED::OLED_SetRowAddress_160128RGB(unsigned char y_start, unsigned char y_end)    // set row address start + end
{
    OLED_Command_160128RGB(0x19);
    OLED_Data_160128RGB(y_start);
    OLED_Command_160128RGB(0x1A);
    OLED_Data_160128RGB(y_end);
}

void SEPS525_OLED::OLED_WriteMemoryStart_160128RGB(void)    // write to RAM command
{
    OLED_Command_160128RGB(0x22);
}

void SEPS525_OLED::OLED_Pixel_160128RGB(unsigned long color)    // write one pixel of a given color
{
  OLED_SerialPixelData_160128RGB((color>>16));
  OLED_SerialPixelData_160128RGB((color>>8));
  OLED_SerialPixelData_160128RGB(color);
}

void SEPS525_OLED::OLED_SetPosition_160128RGB(unsigned char x_pos, unsigned char y_pos)    // set x,y address
{
    OLED_Command_160128RGB(0x20);
    OLED_Data_160128RGB(x_pos);
    OLED_Command_160128RGB(0x21);
    OLED_Data_160128RGB(y_pos);
}

void SEPS525_OLED::OLED_FillScreen_160128RGB(unsigned long color)    // fill screen with a given color
{
   unsigned int i;
   OLED_SetPosition_160128RGB(0,0);
   OLED_WriteMemoryStart_160128RGB();
   for(i=0;i<20480;i++)
   {
      OLED_Pixel_160128RGB(color);
   }
}

/*===============================*/
/*===== LOW LEVEL FUNCTIONS =====*/
/*============= END =============*/
/*===============================*/


/*********************************/
/***** HIGH LEVEL FUNCTIONS ******/
/************ START **************/
/*********************************/

void SEPS525_OLED::OLED_Text_160128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor)  // function to show text
{
    int i;
    int count;
    unsigned char mask = 0x80;
    
    for(i=0;i<8;i++)     // each character is 8 pixels tall
    {
        OLED_SetPosition_160128RGB(x_pos,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<5;count++)    // each character is 5 pixels wide
        {
            if((Ascii_1[letter][count] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
        }
        y_pos++;
        mask = mask >> 1;
   }
}

void SEPS525_OLED::OLED_Text2x_160128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor)  // function to show text (2x size)
{
    int i;
    int count;
    unsigned char mask = 0x80;
    
    for(i=1;i<=16;i++)     // each character is 16 pixels tall
    {
        OLED_SetPosition_160128RGB(x_pos,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<10;count++)    // each character is 10 pixels wide
        {
            if((Ascii_1[letter][(count/2)] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
        }
        y_pos++;
        if((i%2)==0)
        {
          mask = mask >> 1;
        }
   }
}

void SEPS525_OLED::OLED_NHDText_160128RGB(unsigned long textColor, unsigned long backgroundColor)    // function to show NEWHAVEN DISPLAY
{
    int i;
    int count;
    unsigned char index = 0;
    unsigned char y_pos = 110;
    unsigned char mask = 0x80;
    
    for(i=0;i<11;i++)     // display custom character N
    {
        OLED_SetPosition_160128RGB(26,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((N10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((N10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 110;
   
   for(i=0;i<11;i++)     // display custom character E
    {
        OLED_SetPosition_160128RGB(40,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((E10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 110;
   
   for(i=0;i<11;i++)     // display custom character W
    {
        OLED_SetPosition_160128RGB(51,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((W10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((W10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 110;
   
   for(i=0;i<11;i++)     // display custom character H
    {
        OLED_SetPosition_160128RGB(71,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((H10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 110;
   
   for(i=0;i<11;i++)     // display custom character A
    {
        OLED_SetPosition_160128RGB(83,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((A10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((A10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 110;
   
   for(i=0;i<11;i++)     // display custom character V
    {
        OLED_SetPosition_160128RGB(96,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((V10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((V10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 110;
   
   for(i=0;i<11;i++)     // display custom character E
    {
        OLED_SetPosition_160128RGB(110,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((E10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 110;
   
   for(i=0;i<11;i++)     // display custom character N
    {
        OLED_SetPosition_160128RGB(122,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((N10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((N10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character D
    {
        OLED_SetPosition_160128RGB(40,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((D10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;  
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((D10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character I
    {
        OLED_SetPosition_160128RGB(54,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((I10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character S
    {
        OLED_SetPosition_160128RGB(61,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((S10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character P
    {
        OLED_SetPosition_160128RGB(72,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((P10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character L
    {
        OLED_SetPosition_160128RGB(84,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((L10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character A
    {
        OLED_SetPosition_160128RGB(95,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((A10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        for (count=0;count<8;count++)
        {
            if((A10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
   index = 0;
   y_pos = 94;
   
   for(i=0;i<11;i++)     // display custom character Y
    {
        OLED_SetPosition_160128RGB(109,y_pos);
        OLED_WriteMemoryStart_160128RGB();
        for (count=0;count<8;count++)
        {
            if((Y10pt[index] & mask) == mask)
                OLED_Pixel_160128RGB(textColor);
            else
                OLED_Pixel_160128RGB(backgroundColor);
            mask = mask >> 1;
        }
        index++;
        mask = 0x80;
        y_pos--;
   }
}

void SEPS525_OLED::OLED_Icon_160128RGB(unsigned char x_pos, unsigned char y_pos)    // function to show icon
{
   unsigned int i, j;
   unsigned int incr = 0;
   
   for(i=0;i<20;i++)
   {
     OLED_SetPosition_160128RGB(x_pos,y_pos+i);
     OLED_WriteMemoryStart_160128RGB();
     for(j=0;j<60;j+=3)
     {
      OLED_SerialPixelData_160128RGB(smiley20x20[(j+incr)]);
      OLED_SerialPixelData_160128RGB(smiley20x20[((j+incr)+1)]);
      OLED_SerialPixelData_160128RGB(smiley20x20[((j+incr)+2)]);
     }
     incr += 60;
   }
}

void SEPS525_OLED::OLED_Spectrum_160128RGB(void)                  // function to show color spectrum
{
      unsigned char i, j;
      unsigned char blue, green, red;
      
      OLED_SetPosition_160128RGB(0,0);
      OLED_WriteMemoryStart_160128RGB();
      for(i=0;i<160;i++)
      {
        OLED_Pixel_160128RGB(WHITE);
      }
      OLED_SetPosition_160128RGB(0,1);
      OLED_WriteMemoryStart_160128RGB();
      for(i=0;i<160;i++)
      {
        OLED_Pixel_160128RGB(WHITE);
      }
      for(i=0;i<40;i++)
      {
        blue = 0x00;
        green = 0x00;
        red = 0xFF;
        OLED_SetPosition_160128RGB(0,(2+i));
        OLED_WriteMemoryStart_160128RGB();
        OLED_Pixel_160128RGB(WHITE);
        OLED_Pixel_160128RGB(WHITE);
        for(j=0;j<26;j++)
        {
          OLED_Data_160128RGB(blue);
          OLED_Data_160128RGB(green);
          OLED_Data_160128RGB(red);
          green += 9;
        }
        for(j=0;j<26;j++)
        {
          OLED_Data_160128RGB(blue);
          OLED_Data_160128RGB(green);
          OLED_Data_160128RGB(red);
          red -= 9;
        }
        for(j=0;j<26;j++)
        {
          OLED_Data_160128RGB(blue);
          OLED_Data_160128RGB(green);
          OLED_Data_160128RGB(red);
          blue += 9;
        }
        for(j=0;j<26;j++)
        {
          OLED_Data_160128RGB(blue);
          OLED_Data_160128RGB(green);
          OLED_Data_160128RGB(red);
          green -= 9;
        }
        for(j=0;j<26;j++)
        {
          OLED_Data_160128RGB(blue);
          OLED_Data_160128RGB(green);
          OLED_Data_160128RGB(red);
          red += 9;
        }
        for(j=0;j<26;j++)
        {
          OLED_Data_160128RGB(blue);
          OLED_Data_160128RGB(green);
          OLED_Data_160128RGB(red);
          blue -= 9;
        }
        OLED_Pixel_160128RGB(WHITE);
        OLED_Pixel_160128RGB(WHITE);
      }
      
      OLED_SetPosition_160128RGB(0,42);
      OLED_WriteMemoryStart_160128RGB();
      for(i=0;i<160;i++)
      {
        OLED_Pixel_160128RGB(WHITE);
      }
      OLED_SetPosition_160128RGB(0,43);
      OLED_WriteMemoryStart_160128RGB();
      for(i=0;i<160;i++)
      {
        OLED_Pixel_160128RGB(WHITE);
      }
}