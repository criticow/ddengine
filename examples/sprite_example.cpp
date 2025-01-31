#include <ddengine/ddengine.hpp>

const char *vShaderData = R"(
  #version 460 core
  layout (location = 0) in vec2 aPos;

  uniform mat4 projection;
  uniform mat4 model;
  uniform vec4 texCoords1;
  uniform vec4 texCoords2;

  out vec2 TexCoords;

  void main()
  {
    gl_Position = projection * model * vec4(aPos, 0.0f, 1.0f);

    if(gl_VertexID == 0) TexCoords = texCoords1.xy;
    else if(gl_VertexID == 1) TexCoords = texCoords1.zw;
    else if(gl_VertexID == 2) TexCoords = texCoords2.xy;
    else TexCoords = texCoords2.zw;
  }
)";

const char *fShaderData = R"(
  #version 460 core
  
  in vec2 TexCoords;
  uniform sampler2D sampler;

  out vec4 FragColor;

  void main()
  {
    FragColor = texture(sampler, TexCoords);
  }
)";

Shader shader;
Texture texture;
GLuint VAO, VBO, EBO;

std::vector<float> vertices = {
  0.0f, 0.0f,
  0.0f, 1.0f,
  1.0f, 1.0f,
  1.0f, 0.0f
};

std::vector<GLuint> indices = {
  0, 1, 2,
  0, 2, 3
};

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

class Game : public Engine
{
  public:
  Game() : Engine(1280, 720, 1280, 720, "Sprites"){}

  void onUpdate() override
  {
    if(tempo.hasPassed("update_frame", animationDuration / frames.size()))
    {
      frameIndex == frames.size() -1 ? frameIndex = 0 : frameIndex++;
    }
  }

  void onSetup() override
  {
    shader = Shader(vShaderData, fShaderData);
    texture = Texture("data/textures/cadet.png");

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);

    shader.use();
    shader.setInt("sampler", 0);

    texture.bind();
  }

  void onRender() override
  {
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->window.resolutionWidth), static_cast<float>(this->window.resolutionHeight), 0.0f, -1.0f, 1.0f);
    shader.setMatrix("projection", projection);

    glm::mat4 model(1.0f);
    glm::vec2 size(256.0f);

    glm::vec2 position(
      (window.resolutionWidth * 0.5f) - (size.x * 0.5f),
      (window.resolutionHeight * 0.5f) - (size.y * 0.5f)
    );

    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 0.0f));

    shader.setMatrix("model", model);

    auto texCoords = getTexCoords(
      glm::vec4(frames[frameIndex], 32.0f, 32.0f),
      static_cast<float>(texture.width),
      static_cast<float>(texture.height),
      false,
      false
    );

    shader.setFloat("texCoords1", texCoords.first);
    shader.setFloat("texCoords2", texCoords.second);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
  }
};

int main()
{
  Game game;
  game.run();
}