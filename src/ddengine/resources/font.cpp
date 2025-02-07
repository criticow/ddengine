#include "font.hpp"

#include <ddengine/core/engine.hpp>

Font::Font(FontCreateInfo fontCreateInfo)
{
  auto [name, path, size, pixelated] = fontCreateInfo;

  this->name = name;

  FT_Library ft;
  ASSERT(!FT_Init_FreeType(&ft), "Could not initialize FreeType library");

  FT_Face face;
  ASSERT(!FT_New_Face(ft, path.c_str(), 0, &face), "Could not create new font face")

  // Set font size
  FT_Set_Pixel_Sizes(face, 0, size);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // Calculate atlas dimensions
  int atlasWidth = 0;
  int atlasHeight = 0;
  int padding = 3;

  for (unsigned char c = 32; c < 128; c++)
  {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      std::cerr << "Failed to load glyph: " << c << std::endl;
      continue;
    }

    atlasWidth += face->glyph->bitmap.width + padding;
    atlasHeight = std::max(atlasHeight, static_cast<int>(face->glyph->bitmap.rows));

    if(c == 'o')
    {
      this->maxAdvance = face->glyph->bitmap.width;
    }
  }

  this->maxHeight = atlasHeight;

  // Create a buffer for the font atlas
  unsigned char* atlasBuffer = new unsigned char[atlasWidth * atlasHeight]();
  int xOffset = 0;

  // Render glyphs into the atlas
  for (unsigned char c = 32; c < 128; c++)
  {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      std::cerr << "Failed to load glyph: " << c << std::endl;
      continue;
    }

    FT_GlyphSlot glyph = face->glyph;

    // Copy glyph bitmap to atlas buffer
    for (int row = 0; row < glyph->bitmap.rows; row++)
    {
      for (int col = 0; col < glyph->bitmap.width; col++)
      {
        atlasBuffer[(row * atlasWidth) + xOffset + col] =
          glyph->bitmap.buffer[row * glyph->bitmap.width + col];
      }
    }

    // Store character metadata
    characters[c] = {
      static_cast<float>(xOffset),
      0.0f,
      static_cast<float>(glyph->bitmap.width),
      static_cast<float>(glyph->bitmap.rows),
      static_cast<float>(glyph->bitmap_left),
      static_cast<float>(glyph->bitmap_top),
      static_cast<float>(glyph->advance.x) / 64.0f
    };

    xOffset += glyph->bitmap.width + padding;
  }

  this->texture = Engine::resourceManager.addResource<Texture>(name + "_" + std::to_string(size), Texture({
    .width = atlasWidth,
    .height = atlasHeight,
    .buffer = atlasBuffer,
    .pixelated = pixelated
  }));

  // Clean up
  delete[] atlasBuffer;
  FT_Done_Face(face);
  FT_Done_FreeType(ft);
}