#pragma once

#include <ddenginepch.hpp>

struct Mouse
{
  bool firstMouse = true;
  float x = -1.0f;
  float y = -1.0f;
  float lastX;
  float lastY;
};


class Window
{
  public:
  int width;
  int height;
  int resolutionWidth;
  int resolutionHeight;
  GLFWwindow *handle = nullptr;
  Mouse mouse;

  Window(){};
  Window(int width, int height, int resolutionWidth, int resolutionHeight, const char *title);

  bool isOpen();
  void swapBuffers();
  void loadGL();
  void handleEvents(bool waitEvents = false);
  void destroy();
  void clear();
  void setColor(float r, float g, float b, float a);
  void close();
  void setUserPointer();
  void setTitle(const std::string &title);
  void updateViewport();

  static void glDebugOutput(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei len, const char *msg, const void *usrParam);
  static void framebufferSizeCallback(GLFWwindow *handle, int width, int height);
  static void cursorPosCallback(GLFWwindow *handle, double xPos, double yPos);

  private:
  bool isGLLoaded = false;
  bool isFramebufferUpdated = false;
  bool isCursorPosUpdated = false;
  static std::mutex framebufferMutex;
  static std::mutex cursorPosMutex;
};