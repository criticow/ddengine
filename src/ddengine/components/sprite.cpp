#include <ddengine/components/sprite.hpp>

Sprite::Sprite(): Sprite(SpriteCreateInfo{}) {};

Sprite::Sprite(SpriteCreateInfo spriteCreateInfo)
{
  this->texture = spriteCreateInfo.texture;
  this->dimensions = spriteCreateInfo.dimensions;
  this->color = spriteCreateInfo.color;
  this->flipX = spriteCreateInfo.flipX;
  this->flipY = spriteCreateInfo.flipY;
  this->isText = spriteCreateInfo.isText;
  this->state = spriteCreateInfo.state;
}

Sprite::Sprite(const Sprite &other)
{
  this->texture = other.texture;
  this->dimensions = other.dimensions;
  this->color = other.color;
  this->flipX = other.flipX;
  this->flipY = other.flipY;
  this->isText = other.isText;
  this->state = other.state;
}

QuadInstanceData Sprite::getInstanceData(Transform &transform)
{
  auto qid = QuadInstanceData{
    .model = transform.getModel(),
    .color = this->color,
    .textureID = this->texture ? this->texture->index : -1,
    .isText = this->isText,
    .state = this->state,
  };

  if(this->texture)
  {
    auto texCoords = getTexCoords();

    qid.texCoords1 = texCoords.first;
    qid.texCoords2 = texCoords.second;
  }

  return std::move(qid);
}

std::pair<glm::vec4, glm::vec4> Sprite::getTexCoords()
{
  ASSERT(texture, "Invalid texture");

  float totalWidth = static_cast<float>(texture->width);
  float totalHeight = static_cast<float>(texture->height);
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
