#pragma once

#include <ddenginepch.hpp>

#include <ddengine/resources/shader.hpp>
#include <ddengine/resources/resource_manager.hpp>

enum InstanceState
{
  ENABLED,
  DISABLED,
  DELETED
};

/*
  Should set size, stride, drawMode, vertices and indice on the drived constructor
*/
template<typename T>
class Renderer
{
  public:
  Renderer() : instancesCount(0), size(0), stride(0), drawMode(GL_TRIANGLES) {}

  void render(glm::mat4 projection);
  void setup();
  int addInstance(T data);
  void removeInstance(int index);

  virtual void onSetup(){};
  virtual void onRender(glm::mat4 projection){};

  std::vector<T> instancesData;

  protected:
  std::vector<float> vertices;
  std::vector<GLuint> indices;
  std::vector<int> unusedIndexes;
  Shader *shader = nullptr;
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
  GLuint SSBO;
  size_t instancesCount;
  GLuint size;
  GLsizei stride;
  GLenum drawMode;
};

template <typename T>
inline void Renderer<T>::setup()
{
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, this->size, GL_FLOAT, GL_FALSE, this->stride, (void*)0);

  glGenBuffers(1, &SSBO);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO);
  glBufferData(GL_SHADER_STORAGE_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBO);

  // Call the derived setup function
  this->onSetup();
}

template <typename T>
inline int Renderer<T>::addInstance(T data)
{
  int index;

  if(!this->unusedIndexes.empty())
  {
    index = this->unusedIndexes[0];
    this->unusedIndexes.erase(this->unusedIndexes.begin());
    return index;
  }

  this->instancesData.push_back(data);
  index = static_cast<int>(this->instancesData.size() -1);

  return index;
}

template <typename T>
inline void Renderer<T>::removeInstance(int index)
{
  if(this->instancesData.size() -1 < index)
  {
    return;
  }

  this->unusedIndexes.push_back(index);
}

template <typename T>
inline void Renderer<T>::render(glm::mat4 projection)
{
  if(this->instancesData.empty()) return;

  // Call the derived render function
  this->onRender(projection);

  glBindVertexArray(VAO);

  // Bind SSBO to the shader
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, SSBO);

  if(instancesCount != instancesData.size())
  {
    // Change the buffer size and data if the instances array has changed size
    glBufferData(GL_SHADER_STORAGE_BUFFER, instancesData.size() * sizeof(T), instancesData.data(), GL_DYNAMIC_DRAW);
    instancesCount = instancesData.size();
  }
  else
  {
    // Change only the buffer data
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, instancesData.size() * sizeof(T), instancesData.data());
  }

  // Draw all instances
  glDrawElementsInstanced(this->drawMode, static_cast<GLsizei>(this->indices.size()), GL_UNSIGNED_INT, 0, static_cast<GLsizei>(instancesData.size()));

  glBindVertexArray(0);
}