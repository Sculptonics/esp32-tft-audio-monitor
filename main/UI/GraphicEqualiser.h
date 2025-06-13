#pragma once

#include "Component.h"


class GraphicEqualiser : public Component
{
private:

  int m_num_bins;
  float *bar_chart;
  float *bar_chart_peaks;
  uint8_t m_bandNum;
  uint8_t m_rangePart;

public:
  GraphicEqualiser(int x, int y, int width, int height, int num_bins, uint8_t bandNum, uint8_t rangePart);
  void update(float *mag);
  void _draw(u8g2_t &display);
};
