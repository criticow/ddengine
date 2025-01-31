#pragma once

#include <ddenginepch.hpp>

class Texture
{
  public:
  GLuint handle;
  int width;
  int height;
  int index;

  Texture(){};
  // from image file
  Texture(const std::string &path, int index = 0);
  // from font file
  Texture(int width, int height, unsigned char *buffer, bool pixelated = false);

  void bind();
  void destroy();
};