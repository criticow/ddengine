#include "text.hpp"

#include <ddengine/core/engine.hpp>

Text::Text(TextCreateInfo textCreateInfo)
{
  this->font = textCreateInfo.font;
  this->parentTransform = textCreateInfo.parentTransform;
  this->value = textCreateInfo.value;
  this->position = textCreateInfo.position;
  this->rotation = textCreateInfo.rotation;
  this->color = textCreateInfo.color;
  this->layer = textCreateInfo.layer;
  this->display = textCreateInfo.display;

  instances.reserve(value.length());

  this->setup();
}

void Text::setValue(const std::string &value)
{
  if(this->value == value)
  {
    return;
  }

  this->value = value;
  this->isChanged = true;
}

void Text::setPosition(const glm::vec2 &position)
{
  if(this->position == position)
  {
    return;
  }

  this->position = position;
  this->isChanged = true;
}

void Text::setColor(const glm::vec4 &color)
{
  if(this->color == color)
  {
    return;
  }

  this->color = color;
  this->isChanged = true;
}

void Text::setDisplay(int display)
{
  this->display = display;
  this->isChanged = true;
}

void Text::update()
{
  if(!this->isChanged)
  {
    return;
  }

  this->isChanged = false;

  this->setup();
}

void Text::setup()
{
  float offsetX = this->position.x;
  int index = 0;

  Sprite sprite(SpriteCreateInfo{
    .texture = font->texture,
    .color = this->color,
    .isText = true,
    .display = this->display,
  });

  Transform transform;
  transform.parentTransform = this->parentTransform;
  transform.layer = this->layer;

  for(auto c : value)
  {
    auto character = this->font->characters[c];

    if(static_cast<int>(c) == static_cast<int>(' '))
    {
      offsetX += font->maxAdvance;
      continue;
    }

    int size = static_cast<int>(this->instances.size() -1);

    // Insert a new default instance
    if(index > size)
    {
      instances.push_back(Engine::quadRenderer.addInstance(QuadInstanceData()));
    }

    auto &data = Engine::quadRenderer.instancesData.at(this->instances.at(index));

    float heightFiller = this->position.y + font->maxHeight - character.bearingY;

    transform.position = glm::vec2(offsetX, heightFiller);
    transform.size = glm::vec2(character.width, character.height);
    transform.rotation = this->rotation;

    sprite.dimensions = glm::vec4(
      character.xOffset,
      character.yOffset,
      character.width,
      character.height
    );

    data = sprite.getInstanceData(transform);

    offsetX += character.width + 1.0f;
    index++;
  }

  // Delete/disable the unused instances
  if(this->instances.size() > index)
  {
    for(size_t i = index; i < this->instances.size(); i++)
    {
      auto instanceIndex = this->instances.at(i);
      auto &data = Engine::quadRenderer.instancesData.at(instanceIndex);
      
      data.display = QID_DISPLAY_DISABLED;
    }
  }
}
