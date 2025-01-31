#include "resource_manager.hpp"

const int MAX_TEXTURES = 16;

ResourceManager::ResourceManager()
{
  this->textureIDs.reserve(MAX_TEXTURES);

  for(int i = 0; i < MAX_TEXTURES; i++)
  {
    this->textureIDs.push_back(i);
  }
}

Shader* ResourceManager::getShader(const std::string &name)
{
  ASSERT(this->hasResource<Shader>(name), "Shader with name {} not found!", name);
  return &this->shaders.at(name);
}

Shader* ResourceManager::setShader(const std::string &name, const char *vShaderData, const char *fShaderData)
{
  return this->setShader(name, Shader(vShaderData, fShaderData));
}

Shader* ResourceManager::setShader(const std::string &name, Shader shader)
{
  auto [it, inserted] = this->shaders.emplace(name, shader);
  return &it->second;
}

std::vector<Shader> ResourceManager::getShaders()
{
  std::vector<Shader> shadersStored;

  for(auto &[key, value] : ResourceManager::shaders)
  {
    shadersStored.push_back(value);
  }

  return shadersStored;
}

Texture* ResourceManager::getTexture(const std::string &name)
{
  ASSERT(this->hasResource<Texture>(name), "Texture with name {} not found!", name);
  return &this->textures.at(name);
}

Texture* ResourceManager::setTexture(const std::string &name, const std::string &path)
{
  return this->setTexture(name, Texture(path));
}

Texture* ResourceManager::setTexture(const std::string &name, Texture texture)
{
  ASSERT(!this->textureIDs.empty(), "Texture index limit reached");

  auto [it, inserted] = this->textures.emplace(name, texture);
  it->second.index = this->textureIDs[0];

  this->textureIDs.erase(this->textureIDs.begin());

  return &it->second;
}

std::vector<Texture> ResourceManager::getTextures()
{
  std::vector<Texture> texturesStored;

  for(auto &[key, value] : ResourceManager::textures)
  {
    texturesStored.push_back(value);
  }

  return texturesStored;
}