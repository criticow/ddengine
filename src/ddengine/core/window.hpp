#pragma once

#include <ddenginepch.hpp>

class Window
{
  public:
  Window(int width, int height, int resolutionWidth, int resolutionHeight, const char* title);

  int width;
  int height;
  int resolutionWidth;
  int resolutionHeight;
};