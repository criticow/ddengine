#include <ddengine/ddengine.hpp>

QuadRenderer quadRenderer;
LineRenderer lineRenderer;

std::pair<glm::vec4, glm::vec4> getTexCoords(glm::vec4 dimensions, float texWidth, float texHeight, bool flipX, bool flipY)
{
  float totalWidth = texWidth;
  float totalHeight = texHeight;
  float x = dimensions.x;
  float y = dimensions.y;
  float width = dimensions.z;
  float height = dimensions.w;

  glm::vec2 bottomLeft(x / totalWidth, y / totalHeight);
  glm::vec2 topLeft(x / totalWidth, (y + height) / totalHeight);
  glm::vec2 topRight((x + width) / totalWidth, (y + height) / totalHeight);
  glm::vec2 bottomRight((x + width) / totalWidth, y / totalHeight);

  if(flipX && flipY)
  {
    return std::make_pair(glm::vec4(topRight, bottomRight), glm::vec4(bottomLeft, topLeft));
  }
  if(flipX)
  {
    return std::make_pair(glm::vec4(bottomRight, topRight), glm::vec4(topLeft, bottomLeft));
  }
  if(flipY)
  {
    return std::make_pair(glm::vec4(topLeft, bottomLeft), glm::vec4(bottomRight, topRight));
  }

  return std::make_pair(glm::vec4(bottomLeft, topLeft), glm::vec4(topRight, bottomRight));
}

std::vector<glm::vec2> frames = {
  glm::vec2(0.0f, 32.0f),
  glm::vec2(32.0f, 32.0f),
  glm::vec2(64.0f, 32.0f),
  glm::vec2(96.0f, 32.0f),
  glm::vec2(128.0f, 32.0f),
  glm::vec2(160.0f, 32.0f),
  glm::vec2(192.0f, 32.0f),
};

int frameIndex = 0;
float animationDuration = 1000.0f;

class Application : public Engine
{
  public:
  Application(int width, int height, int resolutionWidth, int resolutionHeight, const char* title) : 
    Engine(width, height, resolutionWidth, resolutionHeight, title){};

  void onUpdate() override {
    if(tempo.justUpdated)
    {
      window.setTitle(std::format("{:.2f} MS - {:.2f} FPS - {:.2f} DeltaTime", tempo.ms, tempo.fps, tempo.deltaTime));
    }

    if(tempo.hasPassed("update_frame", animationDuration / frames.size()))
    {
      frameIndex++;
      if(frameIndex == frames.size()) frameIndex = 0;

      for(auto &data : quadRenderer.instancesData)
      {
        auto texture = resourceManager.getTexture("cadet");

        auto texCoords = getTexCoords(glm::vec4(frames[frameIndex], 32.0f, 32.0f), static_cast<float>(texture->width), static_cast<float>(texture->height), false, false);

        data.texCoords1 = texCoords.first;
        data.texCoords2 = texCoords.second;
      }
    }
  };

  void onSetup() override {
    auto texture = resourceManager.setTexture("cadet", "data/textures/cadet.png");

    quadRenderer.setup(this->resourceManager);
    lineRenderer.setup(this->resourceManager);

    for(size_t i = 0; i < 8; i++)
    {
      for(size_t j = 0; j < 8; j++)
      {
        float offsetX = window.resolutionWidth / 8.0f * i + 40.0f;
        float offsetY = window.resolutionHeight / 8.0f * j;

        glm::vec2 position(offsetX, offsetY);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(position, 0.0f));
        model = glm::scale(model, glm::vec3(80.0f, 80.0f, 0.0f));

        QuadInstanceData data;
        data.model = model;
        data.layer = 0;
        data.isText = false;
        data.textureID = texture->index;
        data.color = glm::vec4(0.0f);
        data.strokeColor = glm::vec4(0.0f);
        auto texCoords = getTexCoords(glm::vec4(frames[frameIndex], 32.0f, 32.0f), static_cast<float>(texture->width), static_cast<float>(texture->height), false, false);
        data.texCoords1 = texCoords.first;
        data.texCoords2 = texCoords.second;

        quadRenderer.instancesData.push_back(data);
      }
    }

    // Green lines
    for(size_t i = 0; i < 7; i++)
    {
      float offset = i * 0.125f + 0.125f;

      if(offset == 0.5f) continue; // white lines

      glm::vec4 greenColor(0.0f, 1.0f, 0.0f, 0.125f);

      lineRenderer.instancesData.emplace_back(glm::vec2(0.0f, window.resolutionHeight * offset), glm::vec2(window.resolutionWidth, window.resolutionHeight * offset), greenColor);
      lineRenderer.instancesData.emplace_back(glm::vec2(window.resolutionWidth * offset, 0.0f), glm::vec2(window.resolutionWidth * offset, window.resolutionHeight), greenColor);
    }

    // Blue lines
    for(size_t i = 0; i < 3; i++)
    {
      float offset = i * 0.25f + 0.25f;

      if(offset == 0.5f) continue; // white lines

      glm::vec4 greenColor(0.0f, 0.0f, 1.0f, 0.25f);

      lineRenderer.instancesData.emplace_back(glm::vec2(0.0f, window.resolutionHeight * offset), glm::vec2(window.resolutionWidth, window.resolutionHeight * offset), greenColor);
      lineRenderer.instancesData.emplace_back(glm::vec2(window.resolutionWidth * offset, 0.0f), glm::vec2(window.resolutionWidth * offset, window.resolutionHeight), greenColor);
    }

    // White lines
    lineRenderer.instancesData.emplace_back(glm::vec2(window.resolutionWidth * 0.5f, 0.0f), glm::vec2(window.resolutionWidth * 0.5f, window.resolutionHeight), glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
    lineRenderer.instancesData.emplace_back(glm::vec2(0.0f, window.resolutionHeight * 0.5f), glm::vec2(window.resolutionWidth, window.resolutionHeight * 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
  };
  void onRender() override {
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(window.resolutionWidth), static_cast<float>(window.resolutionHeight), 0.0f, -1.0f, 1.0f);
    lineRenderer.render(projection);
    quadRenderer.render(projection);
  };
};

int main()
{
  Application app(1280, 720, 1280, 720, "Engine Test");
  app.run();
}