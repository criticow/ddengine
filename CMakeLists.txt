cmake_minimum_required(VERSION 3.31.1)

set(CMAKE_CXX_STANDARD 20)
set(DDENGINE_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

project(ddengine CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

add_subdirectory(src)

option(DDENGINE_BUILD_TESTS "Build ddengine tests" ON)
option(DDENGINE_BUILD_EXAMPLES "Build ddengine examples" ON)

if(DDENGINE_BUILD_TESTS)
  add_subdirectory(tests)
endif()

if(DDENGINE_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

############### Dependencies ###############

# GLFW Options
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

# Freetype Options
set(FT_DISABLE_ZLIB ON)
set(FT_DISABLE_BZIP2 ON)
set(FT_DISABLE_PNG ON)
set(FT_DISABLE_BROTLI ON)
set(FT_DISABLE_HARFBUZZ ON)

add_subdirectory(deps/glfw)
add_subdirectory(deps/glad)
add_subdirectory(deps/freetype)

# Script to generate general output header files
execute_process(COMMAND node ${CMAKE_CURRENT_LIST_DIR}/scripts/headers.js)