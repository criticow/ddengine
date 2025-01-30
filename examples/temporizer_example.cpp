#include <ddengine/ddengine.hpp>

Window window(1280, 720, 1280, 720, "Window test");

int main()
{
  Temporizer tempo;

  window.setUserPointer();
  window.loadGL();

  Color color(252, 186, 3, 255);
  window.setColor(color.r, color.g, color.b, color.a);

  while(window.isOpen())
  {
    tempo.update();
    window.handleEvents();

    if(tempo.justUpdated)
    {
      window.setTitle(std::format("{:.2f} ms | {:.2f} fps | {:.2f} delta time", tempo.ms, tempo.fps, tempo.deltaTime));
    }

    window.clear();
    window.swapBuffers();
  }

  window.destroy();

  return 0;
}