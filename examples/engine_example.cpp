#include <ddengine/ddengine.hpp>

class Application : public Engine
{
  public:
  Application(int width, int height, int resolutionWidth, int resolutionHeight, const char* title) : 
    Engine(width, height, resolutionWidth, resolutionHeight, title){};

  void onUpdate() override {};
  void onSetup() override {};
  void onRender() override {};
};

int main()
{
  Application app(1280, 720, 1280, 720, "Engine Test");
  app.run();
}