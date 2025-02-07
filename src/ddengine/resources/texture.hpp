#pragma once

#include <ddenginepch.hpp>

struct TextureCreateInfo
{
  std::string path;
  int width;
  int height;
  unsigned char *buffer = nullptr;
  bool pixelated = false;
};

class Texture
{
  public:
  GLuint handle;
  int width;
  int height;
  static unsigned int index;

  Texture(){};
  Texture(TextureCreateInfo textureCreateInfo);

  void bind();
  void destroy();
  private:
  void fromFile(TextureCreateInfo textureCreateInfo);
  void fromBuffer(TextureCreateInfo textureCreateInfo);
};