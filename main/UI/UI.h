#pragma once

class Palette;
class Waveform;
class GraphicEqualiser;
class Spectrogram;
class U8G2;

class UI
{
private:
  Waveform *m_waveform;
  GraphicEqualiser *m_graphic_equaliser;
  u8g2_t m_display;
  TaskHandle_t m_draw_task_handle;

public:
  UI(u8g2_t &display, int window_size);
  void toggle_display();
  void update(float *samples, float *fft);
  void draw();
  friend void drawing_task(void *param);
};
