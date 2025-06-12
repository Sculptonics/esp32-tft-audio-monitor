#pragma once

#include "Component.h"

class Waveform : public Component
{
private:
  float *m_samples;
  int m_num_samples;

public:
  Waveform(u8g2_t &display, int x, int y, int width, int height, int num_samples);
  void update(const float *samples);
  void _draw(u8g2_t &display);
};
