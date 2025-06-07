
#include "u8g2_esp32_hal.h"
#include "Application.h"

Application *application;



void app_main() {

  application = new Application();
  application->begin();
  // service the application
  while(1){
    application->loop();
  }
}