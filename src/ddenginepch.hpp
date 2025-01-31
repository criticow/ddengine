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

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


#include <ddengine/util/logger.hpp>