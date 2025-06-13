
#include <algorithm>
#include "u8g2_esp32_hal.h"

#include "GraphicEqualiser.h"

#undef min

GraphicEqualiser::GraphicEqualiser(int x, int y, int width, int height, int num_bins, uint8_t bandNum, uint8_t rangePart) : Component(x, y, width, height)
{
  m_bandNum =  bandNum;
  m_rangePart = rangePart;
  m_num_bins = num_bins;
  bar_chart = static_cast<float *>(malloc(sizeof(float) * num_bins));
  for (int i = 0; i < num_bins; i++)
  {
    bar_chart[i] = 0.0f;
  }
  bar_chart_peaks = static_cast<float *>(malloc(sizeof(float) * num_bins));
  for (int i = 0; i < num_bins; i++)
  {
    bar_chart_peaks[i] = 0.0f;
  }
}

void GraphicEqualiser::update(float *mag)
{
  for (int i = 0; i < m_num_bins; i++)
  {
    float m = mag[i];
    if (m > bar_chart[i])
    {
      bar_chart[i] = m;
    }
    else
    {
      bar_chart[i] = 0.7 * bar_chart[i] + 0.3 * m;
    }
    if (m > bar_chart_peaks[i])
    {
      bar_chart_peaks[i] = m;
    }
    else
    {
      bar_chart_peaks[i] = 0.95 * bar_chart_peaks[i] + 0.05 * m;
    }
  }
}

void GraphicEqualiser::_draw(u8g2_t &display)
{
  //u8g2_ClearBuffer(&display);
  int x = 0;
  int x_step = int(width / m_bandNum);
  int x_step_Part = x_step/m_rangePart;
  for (int i = 2; i < m_num_bins / x_step_Part; i += x_step_Part)
  {
    float ave = 0;
    for (int j = 0; j < x_step_Part; j++)
    {
      ave += bar_chart[i + j];
    }
    ave /= 4;
    int bar_value = std::min(height, int(0.1f * ave));
    ave = 0;
    for (int j = 0; j < x_step_Part; j++)
    {
      ave += bar_chart_peaks[i + j];
    }
    ave /= 4;
    int peak_value = std::min(height, int(0.1f * ave));
    //u8g2_DrawBox(&display, x, 0, x_step, height - bar_value - 1);
    u8g2_DrawLine(&display, x, height - peak_value - 1, x + x_step - 1, height - peak_value - 1);
    u8g2_DrawBox(&display, x, height - bar_value - 1, x_step - 1, bar_value);
    x += x_step;
  }
  //u8g2_DrawBox(&display, x, 0, width - x, height);
  //u8g2_SendBuffer(&display);
}