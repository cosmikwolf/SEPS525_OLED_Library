#define seps525_oled_SPI_H

#include <Adafruit_GFX.h>
#include <spi4teensy3.h>

typedef volatile uint8_t PortReg;
typedef uint8_t PortMask;

#define    RED  0x0000FF
#define  GREEN  0x00FF00
#define   BLUE  0xFF0000
#define  WHITE  0xFFFFFF
#define  BLACK  0x000000
#define SEPS525_LCDWIDTH								160
#define SEPS525_LCDHEIGHT								128

// SEPS525 Command List - for more details see: http://www.newhavendisplay.com/app_notes/SEPS525.pdf 
#define SEPS525_INDEX  									0x00  // 
#define SEPS525_STATUS_RD  							0x01  // The status read instruction reads the internal status of the SEPS525. 
#define SEPS525_OSC_CTL  								0x02  // Internal oscillator mode selection
#define SEPS525_IREF  									0x80  // Control reference voltage generation. 
#define SEPS525_CLOCK_DIV  							0x03  // OSC frequency setting / Display frequency divide ration. 
#define SEPS525_REDUCE_CURRENT  				0x04  // Reduced driving current. 
#define SEPS525_SOFT_RST  							0x05  // Soft reset active high.
#define SEPS525_DISP_ON_OFF  						0x06  // Display ON/OFF 
#define SEPS525_PRECHARGE_TIME_R  	 		0x08  // Precharge time R. 
#define SEPS525_PRECHARGE_TIME_G  	 		0x09  // Precharge time G
#define SEPS525_PRECHARGE_TIME_B  	 		0x0A  // Precharge time B. 	
#define SEPS525_PRECHARGE_CURRENT_R  		0x0B  // Precharge current R
#define SEPS525_PRECHARGE_CURRENT_G  		0x0C  // Precharge current G
#define SEPS525_PRECHARGE_CURRENT_B  		0x0D  // Precharge current B
#define SEPS525_DRIVING_CURRENT_R  			0x10  // DCR driving current R.	
#define SEPS525_DRIVING_CURRENT_G  			0x11  // DCG driving current G.	
#define SEPS525_DRIVING_CURRENT_B  			0x12  // DCB driving current B. 	
#define SEPS525_DISPLAY_MODE_SET 	 			0x13  // RGB swap, Scan mode, Row scan shift directio, Column data shift direction. 
#define SEPS525_RGB_IF  								0x14  // RGB interface mode.
#define SEPS525_RGB_POL 								0x15  // Vsync, dot clock polarity, 
#define SEPS525_MEMORY_WRITE_MODE  			0x16  // automatic V+ H increment / decrement
#define SEPS525_MX1_ADDR  							0x17  // Memory Access Window Dimension
#define SEPS525_MX2_ADDR  							0x18  // Memory Access Window Dimension
#define SEPS525_MY1_ADDR  							0x19  // Memory Access Window Dimension
#define SEPS525_MY2_ADDR  							0x1A  // Memory Access Window Dimension
#define SEPS525_MEMORY_ACCESSPOINTER_X  0x20  // horizontal start position of a window for write in memory 
#define SEPS525_MEMORY_ACCESSPOINTER_Y  0x21  // vertical start position of a window for write in memory 
#define SEPS525_DDRAM_DATA_ACCESS_PORT  0x22  // Internal DDRAM memory can be accessed. 
#define SEPS525_GRAY_SCALE_TABLE_INDEX  0x50  // Index register for gamma table
#define SEPS525_GRAY_SCALE_TABLE_DATA 	0x51  // Data register for gamma table. 
#define SEPS525_DUTY  									0x28  // Display duty ratio 0x16~127). 
#define SEPS525_DSL 										0x29  // Display start line 0x0~127-16). 
#define SEPS525_D1_DDRAM_FAC  					0x2E  // First screen display horizontal address for display. 
#define SEPS525_D1_DDRAM_FAR  					0x2F  // First screen display vertical address for display. 
#define SEPS525_D2_DDRAM_SAC  					0x31  // Second screen display horizontal address for Display
#define SEPS525_D2_DDRAM_SAR  					0x32  // Second screen display vertical address for display.
#define SEPS525_SCR1_FX1  							0x33  // The start/end address of active column outputs for the first screen
#define SEPS525_SCR1_FX2  							0x34  // The start/end address of active column outputs for the first screen
#define SEPS525_SCR1_FY1  							0x35  // the start/end address of active row outputs for the second screen 
#define SEPS525_SCR1_FY2  							0x36  // The start/end address of active row outputs for the second screen 
#define SEPS525_SCR2_SX1  							0x37  // 2nd Screen display size horizontal start. 
#define SEPS525_SCR2_SX2  							0x38  // 2nd Screen display size horizontal end. 
#define SEPS525_SCR2_SY1  							0x39  // 2nd Screen display size vertical start.  0x>0x1) 
#define SEPS525_SCR2_SY2  							0x3A  // 2nd Screen display size vertical end. 
#define SEPS525_SCREEN_SAVER_CONTEROL  	0x3B  // 1st, 2nd Screen screen saver control
#define SEPS525_SS_SLEEP_TIMER  				0x3C  // Screen saver sleep timer. 
#define SEPS525_SCREEN_SAVER_MODE  			0x3D  // Screen mode set. 
#define SEPS525_SS_SCR1_FU  						0x3E  // 1st Screen update timer based on frame sync. 
#define SEPS525_SS_SCR1_MXY 						0x3F  // 1st Screen Horizontal moving step. 
#define SEPS525_SS_SCR2_FU  						0x40  // 2nd Screen update timer based on frame sync. 
#define SEPS525_SS_SCR2_MXY 						0x41  // screen moving step
#define SEPS525_MOVING_DIRECTION  			0x42  // 2nd Screen moving direction. 
#define SEPS525_SS_SCR2_SX1  						0x47  // 2nd Screen image box horizontal start address
#define SEPS525_SS_SCR2_SX2  						0x48  // 2nd Screen image box horizontal end address. 
#define SEPS525_SS_SCR2_SY1  						0x49  // 2nd Screen image box vertical start address. 
#define SEPS525_SS_SCR2_SY2  						0x4A  // 2nd Screen image box vertical end address

class seps525_oled : public Adafruit_GFX {
	public:
		seps525_oled(int8_t SDI_PIN, int8_t SCL_PIN, int8_t RS_PIN, int8_t RES_PIN, int8_t CS_PIN);
		seps525_oled(int8_t RS_PIN, int8_t RES_PIN, int8_t CS_PIN);

		void begin(void);
	  void OLED_Init_160128RGB(void);      //OLED initialization

/*
	  void clearDisplay(void);
	  void invertDisplay(uint8_t i);
*/
	  void display();
		void drawPixel(int16_t x, int16_t y, uint16_t color);
		void seps525_command(unsigned char c);     // send command to OLED
		void seps525_data(unsigned char d);        // send data to OLED

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