#pragma once

class U8G2;
class Component
{
public:
  int x, y, width, height;
  bool visible;
  Component(int x, int y, int width, int height) : x(x), y(y), width(width), height(height), visible(true)
  {
  }
  virtual void _draw(u8g2_t &display) = 0;
  void draw(u8g2_t &display)
  {
    if (visible)
    {
      _draw(display);
    }
  }
};