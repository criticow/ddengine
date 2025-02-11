#include "line.hpp"

#include <ddengine/core/engine.hpp>

Line::Line(LineCreateInfo createInfo)
{
  this->start = createInfo.start;
  this->end = createInfo.end;
  this->color = createInfo.color;
  this->layer = createInfo.layer;
  this->state = createInfo.state;

  this->instanceIndex = Engine::lineRenderer.addInstance(LineInstanceData{
    .start = this->start,
    .end = this->end,
    .color = this->color,
    .layer = this->layer,
    .state = this->state
  });
}