#define SEPS525_OLED_SPI_H

#include <Adafruit_GFX.h>
#include <SPI.h>

typedef volatile uint8_t PortReg;
typedef uint8_t PortMask;

#define    RED  0x0000FF
#define  GREEN  0x00FF00
#define   BLUE  0xFF0000
#define  WHITE  0xFFFFFF
#define  BLACK  0x000000

class SEPS525_OLED : public Adafruit_GFX {
	public:
		SEPS525_OLED(int8_t SDI_PIN, int8_t SCL_PIN, int8_t RS_PIN, int8_t RES_PIN, int8_t CS_PIN);
		SEPS525_OLED(int8_t RS_PIN, int8_t RES_PIN, int8_t CS_PIN);

		void begin(void);
	  void OLED_Init_160128RGB(void);      //OLED initialization

		void drawPixel(int16_t x, int16_t y, uint16_t color);
		void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
		void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
		void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
		uint16_t color565(uint8_t r, uint8_t g, uint8_t b);

		void OLED_Command_160128RGB(unsigned char c);        // send command to OLED
		void OLED_Data_160128RGB(unsigned char d);        // send data to OLED
		void OLED_SerialPixelData_160128RGB(unsigned char d);    // serial write for pixel data
		void OLED_SetColumnAddress_160128RGB(unsigned char x_start, unsigned char x_end);    // set column address start + end
		void OLED_SetRowAddress_160128RGB(unsigned char y_start, unsigned char y_end);    // set row address start + end
		void OLED_WriteMemoryStart_160128RGB(void);    // write to RAM command
		void OLED_Pixel_160128RGB(unsigned long color);    // write one pixel of a given color
		void OLED_SetPosition_160128RGB(unsigned char x_pos, unsigned char y_pos);    // set x,y address
		void OLED_FillScreen_160128RGB(unsigned long color);    // fill screen with a given color


		void OLED_Text_160128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor);  // function to show text
		void OLED_Text2x_160128RGB(unsigned char x_pos, unsigned char y_pos, unsigned char letter, unsigned long textColor, unsigned long backgroundColor);  // function to show text (2x size)
		void OLED_NHDText_160128RGB(unsigned long textColor, unsigned long backgroundColor);    // function to show NEWHAVEN DISPLAY
		void OLED_Icon_160128RGB(unsigned char x_pos, unsigned char y_pos);    // function to show icon
		void OLED_Spectrum_160128RGB(void);                  // function to show color spectrum

	private:
		int8_t sdi_pin, scl_pin, rs_pin, res_pin, cs_pin;

	  boolean hwSPI;
	  PortReg *mosiport, *clkport, *csport, *dcport;
	  PortMask mosipinmask, clkpinmask, cspinmask, dcpinmask;

};