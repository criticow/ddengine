#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <format>
#include <string>
#include <ostream>
#include <cstdio>
#include <mutex>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <cmath>
#include <typeinfo>
#include <typeindex>
#include <random>
#include <iomanip>

#include <Windows.h>

#if defined(NDEBUG)
  #define WIN32_LEAN_AND_MEAN
  #undef APIENTRY
#endif
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "util/logger.hpp"