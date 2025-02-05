#include "sprite.hpp"

Sprite::Sprite(): Sprite(SpriteCreateInfo{}) {};

Sprite::Sprite(SpriteCreateInfo spriteCreateInfo)
{
  this->texture = spriteCreateInfo.texture;
  this->dimensions = spriteCreateInfo.dimensions;
  this->color = spriteCreateInfo.color;
  this->flipX = spriteCreateInfo.flipX;
  this->flipY = spriteCreateInfo.flipY;
  this->isText = spriteCreateInfo.isText;
  this->layer = spriteCreateInfo.layer;
  this->display = spriteCreateInfo.display;
}

std::pair<glm::vec4, glm::vec4> Sprite::getTexCoords()
{
  ASSERT(texture, "Invalid texture");

  float totalWidth = texture->width;
  float totalHeight = texture->height;
  float x = dimensions.x;
  float y = dimensions.y;
  float width = dimensions.z;
  float height = dimensions.w;

  glm::vec2 bottomLeft(x / totalWidth, y / totalHeight);
  glm::vec2 topLeft(x / totalWidth, (y + height) / totalHeight);
  glm::vec2 topRight((x + width) / totalWidth, (y + height) / totalHeight);
  glm::vec2 bottomRight((x + width) / totalWidth, y / totalHeight);

  if(flipX && flipY)
  {
    return std::make_pair(glm::vec4(topRight, bottomRight), glm::vec4(bottomLeft, topLeft));
  }
  if(flipX)
  {
    return std::make_pair(glm::vec4(bottomRight, topRight), glm::vec4(topLeft, bottomLeft));
  }
  if(flipY)
  {
    return std::make_pair(glm::vec4(topLeft, bottomLeft), glm::vec4(bottomRight, topRight));
  }

  return std::make_pair(glm::vec4(bottomLeft, topLeft), glm::vec4(topRight, bottomRight));
}
