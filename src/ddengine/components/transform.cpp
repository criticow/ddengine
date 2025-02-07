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
  this->position.z = this->layer / 10.0f;

  glm::mat4 parentModel(1.0f);

  if(parentTransform)
  {
    auto parentPosition = parentTransform->position;
    auto parentRotation = parentTransform->rotation;
    auto parentSize = parentTransform->size;

    parentModel = glm::translate(parentModel, glm::vec3(parentPosition.x, parentPosition.y, 0.0f));

    parentModel = glm::translate(parentModel, glm::vec3(0.5 * parentSize.x, 0.5 * parentSize.y, 0.0f));
    parentModel = glm::rotate(parentModel, glm::radians(parentRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    parentModel = glm::translate(parentModel, glm::vec3(-0.5 * parentSize.x, -0.5 * parentSize.y, 0.0f));
  }

  glm::mat4 model = parentModel;

  model = glm::translate(model, this->position);

  model = glm::translate(model, glm::vec3(0.5 * this->size.x, 0.5 * this->size.y, this->size.z));
  model = glm::rotate(model, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, glm::vec3(-0.5 * this->size.x, -0.5 * this->size.y, this->size.z));

  model = glm::scale(model, this->size);

  return model;
}