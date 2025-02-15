#pragma once

#include "../ddenginepch.hpp"

#include "window.hpp"
#include "temporizer.hpp"
#include "input.hpp"
#include "../resources/resource_manager.hpp"
#include "../renderers/line_renderer.hpp"
#include "../renderers/quad_renderer.hpp"
#include "../components/camera.hpp"

class Engine
{
  // For public use
  public:
  static Window window;
  static Temporizer tempo;
  static Input input;
  static ResourceManager resourceManager;
  static QuadRenderer quadRenderer;
  static LineRenderer lineRenderer;
  static Camera camera;

  void run();

  // For Engine class use only
  private:
  void gameLoop();
  void setup();
  void update();
  void render();
  void destroy();

  // For engine and derived classes use
  protected:
  Engine(int width, int height, int resWidth, int resHeight, const char *title);

  virtual void onUpdate(){};
  virtual void onSetup(){};
  virtual void onRender(){};
};