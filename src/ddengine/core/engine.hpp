#pragma once

#include <ddenginepch.hpp>

#include <ddengine/core/window.hpp>
#include <ddengine/core/temporizer.hpp>
#include <ddengine/core/input.hpp>
#include <ddengine/resources/resource_manager.hpp>
#include <ddengine/renderers/line_renderer.hpp>
#include <ddengine/renderers/quad_renderer.hpp>

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