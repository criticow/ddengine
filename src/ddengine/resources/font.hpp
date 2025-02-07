#pragma once

#include <ddengine/resources/texture.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
  float xOffset;  // Offset in the texture
  float yOffset;  // Offset in the texture
  float width;    // Width in pixels
  float height;   // Height in pixels
  float bearingX; // Offset from baseline to left
  float bearingY; // Offset from baseline to top
  float advance;  // Horizontal offset to advance to the next glyph
};

struct FontCreateInfo
{
  std::string name;
  std::string path;
  unsigned int size = 16;
  bool pixelated = false;
};

class Font
{
  public:
  Font(){};
  Font(FontCreateInfo fontCreateInfo);

  std::string name;
  Texture *texture = nullptr;
  std::unordered_map<char, Character> characters;
  unsigned int maxHeight;
  unsigned int maxAdvance;
};