#include <ddengine/core/engine.hpp>

Window Engine::window;
Temporizer Engine::tempo;
Input Engine::input;
ResourceManager Engine::resourceManager;
QuadRenderer Engine::quadRenderer;
LineRenderer Engine::lineRenderer;
Camera Engine::camera;

Engine::Engine(int width, int height, int resWidth, int resHeight, const char *title)
{
  this->window = Window(width, height, resWidth, resHeight, title);
  this->window.setUserPointer();
}

void Engine::run()
{
  std::thread gameThread(&Engine::gameLoop, this);

  while(this->window.isOpen())
  {
    this->window.handleEvents(true);
  }

  gameThread.join();
  this->destroy();
}

void Engine::gameLoop()
{
  this->setup();
  this->onSetup();

  while(this->window.isOpen())
  {
    this->tempo.update();
    this->input.update(this->window);
    this->window.updateViewport();

    this->update();
    this->onUpdate();

    this->window.clear();

    this->render();
    this->onRender();

    this->window.swapBuffers();
  }
}

void Engine::setup()
{
  this->window.loadGL();
  this->quadRenderer.setup();
  this->lineRenderer.setup();
}

void Engine::update()
{
}

void Engine::render()
{
  this->camera.update(window.resolutionWidth, window.resolutionHeight);
  glm::mat4 viewProjection = this->camera.projection * this->camera.view;

  this->quadRenderer.render(viewProjection);
  this->lineRenderer.render(viewProjection);
}

void Engine::destroy()
{
  this->window.destroy();
}