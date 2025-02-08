#include "quad_renderer.hpp"

#include <ddengine/core/engine.hpp>

QuadRenderer::QuadRenderer()
{
  this->size = 2;
  this->stride = sizeof(float) * 2;
  this->drawMode = GL_TRIANGLES;

  this->vertices = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f
  };

  this->indices = {
    0, 1, 2,
    0, 2, 3
  };
};

void QuadRenderer::onSetup()
{
  const char* vShaderData = R"(
    #version 460 core

    layout (location = 0) in vec2 aPos;

    uniform mat4 projection;

    out vec2 TexCoords;

    struct InstanceData
    {
      mat4 model;
      vec4 color;
      vec4 strokeColor;
      vec4 texCoords1;
      vec4 texCoords2;
      int textureID;
      int isText;
      int layer;
      int display; // 0 enabled, 1 disabled, 2 deleted
    };

    layout (std430, binding = 0) buffer InstancesBuffer {
      InstanceData instancesData[];
    };

    out VS_OUT
    {
      vec2 texCoords;
      flat int textureID;
      vec4 color;
      vec4 strokeColor;
      flat int isText;
    } vs_out;

    void main()
    {
      InstanceData instanceData = instancesData[gl_InstanceID];

      // Dont render this instance
      if(instanceData.display > 0)
      {
        return;
      }

      gl_Position = projection * instanceData.model * vec4(aPos.xy, 0.0, 1.0);

      if(gl_VertexID == 0) vs_out.texCoords = instanceData.texCoords1.xy;
      else if(gl_VertexID == 1) vs_out.texCoords = instanceData.texCoords1.zw;
      else if(gl_VertexID == 2) vs_out.texCoords = instanceData.texCoords2.xy;
      else vs_out.texCoords = instanceData.texCoords2.zw;

      vs_out.textureID = instanceData.textureID;
      vs_out.color = instanceData.color;
      vs_out.strokeColor = instanceData.strokeColor;
      vs_out.isText = instanceData.isText;
    }
  )";

  const char* fShaderData = R"(
    #version 460 core

    out vec4 FragColor;

    uniform sampler2D textures[32];

    in VS_OUT
    {
      vec2 texCoords;
      flat int textureID;
      vec4 color;
      vec4 strokeColor;
      flat int isText;
    } fs_in;

    void main()
    {
      if(fs_in.textureID == -1)
      {
        FragColor = fs_in.color;
        return;
      }

      if(fs_in.isText == 1)
      {
        vec4 sampled = vec4(1.0, 1.0, 1.0, texture(textures[fs_in.textureID], fs_in.texCoords).r);
        if(sampled.a < 0.01)
        {
          discard;
        }

        FragColor = fs_in.color * sampled;
        return;
      }

      FragColor = texture(textures[fs_in.textureID], fs_in.texCoords);
    }
  )";

  this->shader = Engine::resourceManager.addResource<Shader>("quad_default", Shader{vShaderData, fShaderData});
};

void QuadRenderer::onRender(glm::mat4 projection)
{
  shader->use();
  shader->setMatrix("projection", projection);

  auto textureStorage = Engine::resourceManager.getStorage<Texture>();

  for(auto &[key, texture] : textureStorage.resources)
  {
    shader->setInt(std::format("textures[{}]", texture.index), texture.index);
    texture.bind();
  }
}
int QuadRenderer::addInstance(QuadInstanceData data)
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
};