#include <ddengine/components/line.hpp>

#include <ddengine/core/engine.hpp>

Line::Line(LineCreateInfo createInfo)
{
  this->position = createInfo.position;
  this->length = createInfo.length;
  this->color = createInfo.color;
  this->layer = createInfo.layer;
  this->state = createInfo.state;

  this->instanceIndex = Engine::lineRenderer.addInstance(this->generateData());
}

void Line::setPosition(const glm::vec2 &position)
{
  if(this->position == position)
  {
    return;
  }

  this->position = position;
  this->changed = true;
}

void Line::setLength(const glm::vec2 &length)
{
  if(this->length == length)
  {
    return;
  }

  this->length = length;
  this->changed = true;
}

void Line::setColor(const glm::vec4 &color)
{
  if(this->color == color)
  {
    return;
  }

  this->color = color;
  this->changed = true;
}

void Line::setState(InstanceState state)
{
  if(this->state == state)
  {
    return;
  }

  this->state = state;
  this->changed = true;
}

void Line::setLayer(int layer)
{
  if(this->layer == layer)
  {
    return;
  }

  this->layer = layer;
  this->changed = true;
}

void Line::update()
{
  if(!this->changed)
  {
    return;
  }

  Engine::lineRenderer.instancesData[this->instanceIndex] = this->generateData();
  this->changed = false;
}

LineInstanceData Line::generateData()
{
  return LineInstanceData{
    .start = this->position,
    .end = glm::vec2(this->position + this->length),
    .color = this->color,
    .layer = this->layer,
    .state = this->state
  };
}
