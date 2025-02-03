#include "window.hpp"

std::mutex Window::framebufferMutex;
std::mutex Window::cursorPosMutex;

Window::Window(int width, int height, int resolutionWidth, int resolutionHeight, const char *title)
{
  this->width = width;
  this->height = height;
  this->resolutionWidth = resolutionWidth;
  this->resolutionHeight = resolutionHeight;

  ASSERT(glfwInit(), "Could not initialize GLFW");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  #ifndef NDEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
  #endif

  this->handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
  ASSERT(this->handle, "Could not create GLFW window");

  LOGGER_DEBUG("Created Window");

  // Center the window on the primary monitor
  GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
  int offsetX, offsetY, windowWidth, windowHeight;

  glfwGetMonitorPos(primaryMonitor, &offsetX, &offsetY);
  glfwGetWindowSize(this->handle, &windowWidth, &windowHeight);
  const GLFWvidmode *mode = glfwGetVideoMode(primaryMonitor);
  glfwSetWindowPos(this->handle, offsetX + (mode->width - windowWidth) / 2, offsetY + (mode->height - windowHeight) / 2);

  LOGGER_DEBUG("Centered Window");

  glfwSetWindowAspectRatio(this->handle, 16, 9);

  glfwSetFramebufferSizeCallback(this->handle, this->framebufferSizeCallback);
  glfwSetCursorPosCallback(this->handle, cursorPosCallback);
}

bool Window::isOpen()
{
  return !glfwWindowShouldClose(this->handle);
}

void Window::swapBuffers()
{
  glfwSwapBuffers(this->handle);
}

void Window::handleEvents(bool waitEvents)
{
  waitEvents ? glfwWaitEvents() : glfwPollEvents();
}

void Window::destroy()
{
  glfwDestroyWindow(this->handle);
  glfwTerminate();
  LOGGER_DEBUG("Destroyed Window");
}

void Window::loadGL()
{
  glfwMakeContextCurrent(this->handle);

  ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Could not load OpenGL");

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  int flags;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  if(flags & GL_CONTEXT_FLAG_DEBUG_BIT)
  {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(this->glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    LOGGER_DEBUG("Set OpenGL Debugger");
  }

  this->isGLLoaded = true;

  LOGGER_DEBUG("Loaded OpenGL: {}.{}", GLVersion.major, GLVersion.minor);
}

void Window::setColor(float r, float g, float b, float a)
{
  ASSERT(this->isGLLoaded, "Could not change clear color, OpenGL is not loaded");
  glClearColor(r, g, b, a);
}

void Window::setTitle(const std::string &title)
{
  glfwSetWindowTitle(this->handle, title.c_str());
}

void Window::clear()
{
  ASSERT(this->isGLLoaded, "Could not clear buffer, OpenGL is not loaded");
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::setUserPointer()
{
  glfwSetWindowUserPointer(this->handle, this);
  LOGGER_DEBUG("Set Window user pointer");
}

void Window::close()
{
  glfwSetWindowShouldClose(this->handle, GLFW_TRUE);
  LOGGER_DEBUG("Closed Window");
}

void Window::updateViewport()
{
  ASSERT(this->isGLLoaded, "OpenGL is not loaded");

  this->framebufferMutex.lock();

  if(this->isFramebufferUpdated)
  {
    this->isFramebufferUpdated = false;

    auto dimensions = getViewportDimensions(width, height, resolutionWidth, resolutionHeight);

    // Set the OpenGL viewport
    glViewport(dimensions.x, dimensions.y, dimensions.z, dimensions.w);
  }

  this->framebufferMutex.unlock();
}

void Window::framebufferSizeCallback(GLFWwindow *handle, int width, int height)
{
  // Do nothing
  if(width == 0 || height == 0)
  {
    return;
  }

  Window *windowPointer = reinterpret_cast<Window *>(glfwGetWindowUserPointer(handle));
  ASSERT(windowPointer, "Could not find window user pointer");

  windowPointer->framebufferMutex.lock();
  windowPointer->isFramebufferUpdated = true;
  windowPointer->width = width;
  windowPointer->height = height;
  windowPointer->framebufferMutex.unlock();
}

void Window::cursorPosCallback(GLFWwindow *handle, double xPos, double yPos)
{
  Window *windowPointer = reinterpret_cast<Window*>(glfwGetWindowUserPointer(handle));
  ASSERT(windowPointer, "Could not find window user pointer");

  windowPointer->cursorPosMutex.lock();
  windowPointer->isCursorPosUpdated = true;

  auto &mouse = windowPointer->mouse;
  auto width = windowPointer->width;
  auto height = windowPointer->height;
  auto resolutionWidth = windowPointer->resolutionWidth;
  auto resolutionHeight = windowPointer->resolutionHeight;

  auto viewportDimensions = windowPointer->getViewportDimensions(
    width,
    height,
    resolutionWidth,
    resolutionHeight
  );

  if(mouse.firstMouse)
  {
    mouse.firstMouse = false;
    mouse.clientX = static_cast<float>(xPos);
    mouse.clientY = static_cast<float>(yPos);
  }
  
  // Update mouse position
  mouse.lastX = mouse.clientX;
  mouse.lastY = mouse.clientY;

  // Update mouse last position
  mouse.clientX = static_cast<float>(xPos);
  mouse.clientY = static_cast<float>(yPos);

  // should use the available viewport as base instead of the window width/height
  float scaleX = static_cast<float>(viewportDimensions.z) / resolutionWidth;
  float scaleY = static_cast<float>(viewportDimensions.w) / resolutionHeight;

  // calculate the world x/y base on the resolution
  mouse.x = (mouse.clientX - viewportDimensions.x) / scaleX;
  mouse.y = (mouse.clientY - viewportDimensions.y) / scaleY;

  windowPointer->cursorPosMutex.unlock();
}

glm::vec4 Window::getViewportDimensions(int width, int height, int resolutionWidth, int resolutionHeight)
{
  // Update scaling factors
  float scaleX = static_cast<float>(width) / this->resolutionWidth;
  float scaleY = static_cast<float>(height) / this->resolutionHeight;

  // Maintain the aspect ratio
  float aspectGame = static_cast<float>(this->resolutionWidth) / this->resolutionHeight;
  float aspectWindow = static_cast<float>(width) / height;

  int viewportWidth;
  int viewportHeight;

  if (aspectWindow > aspectGame) {
    viewportHeight = height;
    viewportWidth = static_cast<int>(height * aspectGame);
  } else {
    viewportWidth = width;
    viewportHeight = static_cast<int>(width / aspectGame);
  }

  int viewportX = (width - viewportWidth) / 2;
  int viewportY = (height - viewportHeight) / 2;

  return glm::vec4(viewportX, viewportY, viewportWidth, viewportHeight);
}

void Window::glDebugOutput(GLenum src, GLenum type, GLuint id, GLenum severity, GLsizei len, const char *msg, const void *usrParam)
{
  // ignore non-significant error/warning codes
  if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

  std::ostringstream sstream;

  sstream << "\nDebug message (" << id << "): " << msg << "\n";

  switch (src)
  {
    case GL_DEBUG_SOURCE_API:             sstream << "Source: API\n"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   sstream << "Source: Window System\n"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: sstream << "Source: Shader Compiler\n"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     sstream << "Source: Third Party\n"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     sstream << "Source: Application\n"; break;
    case GL_DEBUG_SOURCE_OTHER:           sstream << "Source: Other\n"; break;
  }

  switch (type)
  {
    case GL_DEBUG_TYPE_ERROR:               sstream << "Type: Error\n"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: sstream << "Type: Deprecated Behaviour\n"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  sstream << "Type: Undefined Behaviour\n"; break; 
    case GL_DEBUG_TYPE_PORTABILITY:         sstream << "Type: Portability\n"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         sstream << "Type: Performance\n"; break;
    case GL_DEBUG_TYPE_MARKER:              sstream << "Type: Marker\n"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          sstream << "Type: Push Group\n"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           sstream << "Type: Pop Group\n"; break;
    case GL_DEBUG_TYPE_OTHER:               sstream << "Type: Other\n"; break;
  }
  
  switch (severity)
  {
    case GL_DEBUG_SEVERITY_HIGH:         sstream << "Severity: high\n"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       sstream << "Severity: medium\n"; break;
    case GL_DEBUG_SEVERITY_LOW:          sstream << "Severity: low\n"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: sstream << "Severity: notification\n"; break;
  }

  LOGGER_ERROR(sstream.str());
}