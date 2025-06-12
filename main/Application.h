
#pragma once

#include <driver/i2s.h>

class UI;
class Processor;
class I2SSampler;
class U8G2;

class Application
{
private:
  int m_window_size;
  int16_t *m_sample_buffer;
  UI *m_ui;
  Processor *m_processor;
  I2SSampler *m_sampler;

  void process_samples();

public:
  Application(u8g2_t &display);
  void begin();
  void loop();

  friend void processing_task(void *param);
};