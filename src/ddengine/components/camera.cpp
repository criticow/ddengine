#include <ddengine/components/camera.hpp>

Camera::Camera(glm::vec2 position, float rotation)
{
  this->position = position;
  this->rotation = rotation;
}

void Camera::update(int resolutionWidth, int resolutionHeight)
{
  this->projection = glm::ortho(
    0.0f,
    static_cast<float>(resolutionWidth),
    static_cast<float>(resolutionHeight),
    0.0f,
    -1.0f,
    1.0f
  );

  this->view = glm::translate(glm::mat4(1.0f), -glm::vec3(this->position, 0.0f));
}