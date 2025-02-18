#include "line.hpp"

#include "../core/engine.hpp"

Line::Line(LineCreateInfo createInfo)
{
  this->start = createInfo.start;
  this->end = createInfo.end;
  this->color = createInfo.color;
  this->layer = createInfo.layer;
  this->state = createInfo.state;

  this->instanceIndex = Engine::lineRenderer.addInstance(this->generateData());
}

void Line::setStart(const glm::vec2 &start)
{
  if(this->start == start)
  {
    return;
  }

  this->start = start;
  this->changed = true;
}

void Line::setEnd(const glm::vec2 &end)
{
  if(this->end == end)
  {
    return;
  }

  this->end = end;
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
    .start = this->start,
    .end = this->end,
    .color = this->color,
    .layer = this->layer,
    .state = this->state
  };
}
