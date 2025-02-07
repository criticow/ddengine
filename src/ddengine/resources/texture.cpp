#include "texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

const unsigned int MAX_TEXTURES = 16;

unsigned int Texture::index = 0;

Texture::Texture(TextureCreateInfo textureCreateInfo)
{
  ASSERT(index < MAX_TEXTURES, "Reached max amount of textures. Amount: {}", MAX_TEXTURES);

  this->index = index;

  index++;

  if(textureCreateInfo.buffer)
  {
    fromBuffer(textureCreateInfo);

    return;
  }

  fromFile(textureCreateInfo);
}

void Texture::bind()
{
  glActiveTexture(GL_TEXTURE0 + index);
  glBindTexture(GL_TEXTURE_2D, this->handle);
}

void Texture::destroy()
{
  glDeleteTextures(1, &this->handle);
}

void Texture::fromFile(TextureCreateInfo textureCreateInfo)
{
  auto path = textureCreateInfo.path;
  this->width = textureCreateInfo.width;
  this->height = textureCreateInfo.height;

  
  glGenTextures(1, &this->handle);
  glBindTexture(GL_TEXTURE_2D, this->handle);

  int channels;
  unsigned char *data = stbi_load(path.c_str(), &this->width, &this->height, &channels, 0);

  ASSERT(data, "Could not load texture {}", path);

  GLenum format;

  if(channels == 1) { format = GL_RED; }
  else if(channels == 3) { format = GL_RGB; }
  else { format = GL_RGBA; }

  glTexImage2D(GL_TEXTURE_2D, 0, format, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glBindTexture(GL_TEXTURE_2D, 0);

  stbi_image_free(data);

}

void Texture::fromBuffer(TextureCreateInfo textureCreateInfo)
{
  auto pixelated = textureCreateInfo.pixelated;
  auto buffer = textureCreateInfo.buffer;
  this->width = textureCreateInfo.width;
  this->height = textureCreateInfo.height;

  glGenTextures(1, &this->handle);

  glBindTexture(GL_TEXTURE_2D, this->handle);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, buffer);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pixelated ? GL_NEAREST : GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pixelated ? GL_NEAREST : GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);
}
