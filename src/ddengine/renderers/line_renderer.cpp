#include <ddengine/renderers/line_renderer.hpp>

#include <ddengine/core/engine.hpp>

LineRenderer::LineRenderer()
{
  this->size = 1;
  this->stride = sizeof(float);
  this->drawMode = GL_LINES;

  this->vertices = {
    0.0f, 1.0f,
  };

  this->indices = {
    0, 1
  };
};

void LineRenderer::onSetup()
{
  const char *vShaderData = R"(
    #version 460 core

    layout (location = 0) in float yIndex;

    uniform mat4 projection;

    struct InstanceData
    {
      vec2 start;
      vec2 end;
      vec4 color;
      int layer;
      int state;
      int padding[2];
    };

    layout (std430, binding = 0) buffer InstancesBuffer {
      InstanceData instancesData[];
    };

    out vec4 color;
    out flat int state;

    void main()
    {
      InstanceData instanceData = instancesData[gl_InstanceID];

      vec2 position = mix(instanceData.start, instanceData.end, yIndex);
      gl_Position = projection * vec4(position, instanceData.layer / 10.0, 1.0);

      color = instanceData.color;
      state = instanceData.state;
    }
  )";

  const char *fShaderData = R"(
    #version 460 core

    in vec4 color;
    in flat int state;
    out vec4 FragColor;

    void main()
    {
      if(state > 0)
      {
        discard;
      }

      FragColor = color;
    }
  )";

  this->shader = Engine::resourceManager.addResource<Shader>("line_default", Shader{vShaderData, fShaderData});
};

void LineRenderer::onRender(glm::mat4 projection)
{
  shader->use();
  shader->setMatrix("projection", projection);
};