#include <ddengine/ddengine.hpp>

Window window(1280, 720, 1280, 720, "Window test");
Input input;

int main()
{
  window.setUserPointer();

  window.loadGL();

  Color color(252, 186, 3, 255);
  window.setColor(color.r, color.g, color.b, color.a);

  while(window.isOpen())
  {
    window.handleEvents();
    input.update(window);

    if(input.pressed(KEY_1))
    {
      LOGGER_DEBUG("Key 1 pressed");
    }

    if(input.held(KEY_2))
    {
      LOGGER_DEBUG("Key 2 held");
    }

    if(input.pressed(MOUSE_BUTTON_LEFT))
    {
      LOGGER_DEBUG("Mouse left button clicked");
    }

    if(input.held(MOUSE_BUTTON_RIGHT))
    {
      LOGGER_DEBUG("Mouse right button held");
    }

    window.clear();
    window.swapBuffers();
  }

  window.destroy();

  return 0;
}