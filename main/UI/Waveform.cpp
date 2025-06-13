
#include "u8g2_esp32_hal.h"
#include <cstring>
#include "Waveform.h"

Waveform::Waveform(u8g2_t &display, int x, int y, int width, int height, int num_samples) : Component(x, y, width, height)
{
  m_num_samples = num_samples;
  m_samples = static_cast<float *>(malloc(sizeof(float) * num_samples));
}

void Waveform::update(const float *samples)
{
  memcpy(m_samples, samples, sizeof(float) * m_num_samples);
}

void Waveform::_draw(u8g2_t &display)
{
  //u8g2_ClearBuffer(&display);
  float x = 0;
  float x_step = (float)width / (float)m_num_samples;
  //u8g2_DrawBox(&display, x, y, width, height);
  for (int i = 4; i < m_num_samples; i += 4)
  {
    u8g2_DrawLine(&display, x, height / 2 + m_samples[i - 4] * 1, x + x_step * 4, height / 2 + m_samples[i] * 1);
    x += x_step * 4;
  }
  //u8g2_SendBuffer(&display);
}