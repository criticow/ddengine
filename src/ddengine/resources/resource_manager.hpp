#pragma once

#include <ddenginepch.hpp>

#include <ddengine/resources/shader.hpp>
#include <ddengine/resources/texture.hpp>
#include <ddengine/resources/font.hpp>

class ResourceManager
{
  public:
  ResourceManager();

  Shader* getShader(const std::string &name);
  Shader* setShader(const std::string &name, const char *vShaderData, const char *fShaderData);
  Shader* setShader(const std::string &name, Shader shader);
  std::vector<Shader> getShaders();

  Texture* getTexture(const std::string &name);
  Texture* setTexture(const std::string &name, const std::string &path);
  Texture* setTexture(const std::string &name, Texture texture);
  std::vector<Texture> getTextures();

  Font* getFont(const std::string &name);
  Font* setFont(const std::string &name, const std::string &path, unsigned int size, bool pixelated = false);
  Font* setFont(const std::string &name, Font font);
  std::vector<Font> getFonts();

  template<typename T>
  bool hasResource(const std::string &name)
  {
    if(std::is_same<T, Shader>::value)
    {
      return this->shaders.find(name) != this->shaders.end();
    }

    if(std::is_same<T, Texture>::value)
    {
      return this->textures.find(name) != this->textures.end();
    }

    if(std::is_same<T, Font>::value)
    {
      return this->fonts.find(name) != this->fonts.end();
    }

    return false;
  }

  protected:
  std::unordered_map<std::string, Shader> shaders;
  std::unordered_map<std::string, Texture> textures;
  std::unordered_map<std::string, Font> fonts;
  std::vector<int> textureIDs;
};