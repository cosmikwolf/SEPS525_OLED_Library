#include <Adafruit_GFX.h>
#include <SPI.h>
#include <seps525_oled_SPI.h>

//seps525_oled display(11, 13, 16, 15, 10);
seps525_oled display(16, 15, 10);

void setup(){

   Serial.println("setup start");
   delay(300);
   display.begin();
   Serial.begin(9600);
   Serial.println("setup complete");
   delay(300);
   display.OLED_Init_160128RGB();                           // initialize display
   delay(300);

}

void loop(){

   Serial.println("loop start");


   display.OLED_FillScreen_160128RGB(BLACK);                // fill screen with black


   display.OLED_NHDText_160128RGB(GREEN, BLACK);            // show NEWHAVEN DISPLAY
         delay(300);

   display.OLED_Text_160128RGB(20, 58, 40, WHITE, BLACK);   // H
   display.OLED_Text_160128RGB(27, 58, 69, WHITE, BLACK);   // e
   display.OLED_Text_160128RGB(34, 58, 76, WHITE, BLACK);   // l
   display.OLED_Text_160128RGB(41, 58, 76, WHITE, BLACK);   // l
   display.OLED_Text_160128RGB(48, 58, 79, WHITE, BLACK);   // o
   display.OLED_Text_160128RGB(55, 58, 0, WHITE, BLACK);    //
         delay(300);

   display.OLED_Text_160128RGB(62, 58, 55, WHITE, BLACK);   // W
   display.OLED_Text_160128RGB(69, 58, 79, WHITE, BLACK);   // o
   display.OLED_Text_160128RGB(76, 58, 82, WHITE, BLACK);   // r
   display.OLED_Text_160128RGB(83, 58, 76, WHITE, BLACK);   // l
   display.OLED_Text_160128RGB(90, 58, 68, WHITE, BLACK);   // d
   display.OLED_Text_160128RGB(97, 58, 1, WHITE, BLACK);    // !
         delay(300);

   display.OLED_Icon_160128RGB(120, 52);                    // show icon
         delay(300);

   display.OLED_Spectrum_160128RGB();                       // show color spectrum
         delay(300);
            display.OLED_FillScreen_160128RGB(WHITE);                // fill screen with black
   display.OLED_FillScreen_160128RGB(RED);                // fill screen with black
   display.OLED_FillScreen_160128RGB(GREEN);                // fill screen with black
   display.OLED_FillScreen_160128RGB(BLUE);                // fill screen with black
   display.OLED_FillScreen_160128RGB(BLACK);                // fill screen with black


  display.OLED_SetPosition_160128RGB(0,30);
   display.OLED_WriteMemoryStart_160128RGB();
   for(int i=0;i<100;i++)
   {
      display.OLED_Pixel_160128RGB(BLUE);
   }


  //display.drawPixel(80,50,100);
  //display.drawPixel(80,51,RED);
  //display.drawPixel(80,52,RED);
  //display.drawPixel(80,53,0xFFFFFF);
  //display.drawPixel(80,54,0xFFFFFF);
  //display.drawPixel(80,55,0xFFFFFF);
  //display.drawPixel(80,56,0xFFFFFF);
  //display.drawPixel(80,57,RED);
  //display.drawPixel(80,58,RED);
  //display.drawPixel(80,59,RED);
   //display.display();
   delay(1000);
     display.OLED_Init_160128RGB();                           // initialize display


}