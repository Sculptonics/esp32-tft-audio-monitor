#pragma once

#include "Component.h"


class GraphicEqualiser : public Component
{
private:

  int m_num_bins;
  float *bar_chart;
  float *bar_chart_peaks;

public:
  GraphicEqualiser(int x, int y, int width, int height, int num_bins);
  void update(float *mag);
  void _draw(u8g2_t &display);
};
