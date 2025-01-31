#include <ddengine/ddengine.hpp>



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

class Application : public Engine
{
  public:
  Application(int width, int height, int resolutionWidth, int resolutionHeight, const char* title) : 
    Engine(width, height, resolutionWidth, resolutionHeight, title){};

  void onUpdate() override {};
  void onSetup() override {
    resourceManager.setFont("Arial", "data/fonts/arial.ttf", 16);
    resourceManager.setFont("Dogica", "data/fonts/dogica.ttf", 16, true);
    resourceManager.setFont("Times New Roman", "data/fonts/times.ttf", 16);
    resourceManager.setFont("Comic Sans", "data/fonts/comic.ttf", 16);

    std::string text = "Lorem ipsum dolor sit amet consectetur, adipisicing elit. Temporibus, consequuntur?";

    float baseHeight = 0;
    int colorIndex = 0;

    glm::vec4 colors[] = {
      glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
      glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
      glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
      glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
    };

    for(auto font : resourceManager.getFonts())
    {
      std::string fontText = font.name + " - " + text;
      float offsetX = 0;

      for(auto c : fontText)
      {
        auto character = font.characters[c];

        if(static_cast<int>(c) == static_cast<int>(' '))
        {
          offsetX += font.maxAdvance;
          continue;
        }

        float heightFiller = baseHeight + font.maxHeight - character.bearingY;

        glm::vec2 position(offsetX, heightFiller);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(position, 0.0f));
        model = glm::scale(model, glm::vec3(character.width, character.height, 0.0f));

        QuadInstanceData data;
        data.model = model;
        data.layer = 0;
        data.isText = true;
        data.textureID = font.texture->index;
        data.color = colors[colorIndex];
        data.strokeColor = glm::vec4(0.0f);
        auto texCoords = getTexCoords(glm::vec4(character.xOffset, character.yOffset, character.width, character.height), static_cast<float>(font.texture->width), static_cast<float>(font.texture->height), false, false);
        data.texCoords1 = texCoords.first;
        data.texCoords2 = texCoords.second;

        quadRenderer.instancesData.push_back(data);

        offsetX += character.width + 1.0f;
      }

      baseHeight += font.maxHeight + 10.0f;
      colorIndex++;
    }
  };
  void onRender() override {};
};

int main()
{
  Application app(1280, 720, 1280, 720, "Engine Test");
  app.run();
}