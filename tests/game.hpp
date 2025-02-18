#pragma once

#include <ddengine/ddengine.hpp>

class Game : public Engine
{
  public:
  Game(int width, int height, int resWidth, int resHeight, const char *title) : 
    Engine(width, height, resWidth, resHeight, title){};

  // This method is called in the end of the main update
  void onUpdate() override
  {
  };

  // This method is called in the end of the main setup
  void onSetup() override
  {
  };

  void onRender() override
  {
  };
};