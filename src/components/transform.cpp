#include "transform.hpp"

Transform::Transform(TransformCreateInfo transformCreateInfo)
{
  this->parentTransform = transformCreateInfo.parentTransform;
  this->position = transformCreateInfo.position;
  this->size = transformCreateInfo.size;
  this->rotation = transformCreateInfo.rotation;
  this->layer = transformCreateInfo.layer;
}

Transform::Transform(const Transform &other)
{
  this->parentTransform = other.parentTransform;
  this->position = other.position;
  this->size = other.size;
  this->rotation = other.rotation;
  this->layer = other.layer;
}

glm::mat4 Transform::getModel()
{
  glm::mat4 parentModel(1.0f);

  if(parentTransform)
  {
    auto parentPosition = parentTransform->position;
    auto parentRotation = parentTransform->rotation;
    auto parentSize = parentTransform->size;

    parentModel = glm::translate(parentModel, glm::vec3(parentPosition.x, parentPosition.y, 0.0f));

    parentModel = glm::translate(parentModel, glm::vec3(0.5 * parentSize.x, 0.5 * parentSize.y, 0.0f));
    parentModel = glm::rotate(parentModel, glm::radians(parentRotation), glm::vec3(0.0f, 0.0f, 1.0f));
    parentModel = glm::translate(parentModel, glm::vec3(-0.5 * parentSize.x, -0.5 * parentSize.y, 0.0f));
  }

  glm::mat4 model = parentModel;

  // Make the sprites lower on the window appear at front if the layers are the same
  // Camera must be [-10, 10]
  float adjustedZ = (this->layer / 10.0f) + ((this->position.y + this->size.y) * 0.0001f);

  model = glm::translate(model, glm::vec3(this->position, adjustedZ));

  model = glm::translate(model, glm::vec3(0.5 * this->size.x, 0.5 * this->size.y, 0.0f));
  model = glm::rotate(model, glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, glm::vec3(-0.5 * this->size.x, -0.5 * this->size.y, 0.0f));

  model = glm::scale(model, glm::vec3(this->size, 0.0f));

  return model;
}