#include <ddengine/ddengine.hpp>

Window window(1280, 720, 1280, 720, "Window test");

void gameLoop()
{
  window.loadGL();
  Color color(252, 186, 3, 255);
  window.setColor(color.r, color.g, color.b, color.a);

  while(window.isOpen())
  {
    window.updateViewport();
    window.clear();
    window.swapBuffers();
  }
}

int main()
{
  window.setUserPointer();

  std::thread gameThread(gameLoop);

  while(window.isOpen())
  {
    window.handleEvents(true);
  }

  gameThread.join();

  window.destroy();

  return 0;
}