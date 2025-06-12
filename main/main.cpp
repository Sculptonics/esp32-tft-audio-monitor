
#include "u8g2_esp32_hal.h"
#include "Application.h"

Application *application;
u8g2_t u8g2;
#define PIN_SDA             GPIO_NUM_5
#define PIN_SCL             GPIO_NUM_6

extern "C" void app_main() {
   // initialize the u8g2 hal
	u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
	u8g2_esp32_hal.sda = PIN_SDA;
	u8g2_esp32_hal.scl = PIN_SCL;
	u8g2_esp32_hal_init(u8g2_esp32_hal);

	// initialize the u8g2 library
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(
		&u8g2,
		U8G2_R0,
		u8g2_esp32_i2c_byte_cb,
		u8g2_esp32_gpio_and_delay_cb);
	
	// set the display address
	u8x8_SetI2CAddress(&u8g2.u8x8, 0x78);
	
	// initialize the display
	u8g2_InitDisplay(&u8g2);
	
	// wake up the display
	u8g2_SetPowerSave(&u8g2, 0);
  

  application = new Application(u8g2);
  application->begin();
  // service the application
  while(1){
    application->loop();
  }
}