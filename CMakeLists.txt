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

add_subdirectory(deps/glfw)
add_subdirectory(deps/glad)

# Run the JS file using Node.js during configuration
execute_process(
  COMMAND node ${CMAKE_SOURCE_DIR}/scripts/headers.js
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  RESULT_VARIABLE JS_RESULT
  OUTPUT_VARIABLE JS_OUTPUT
  ERROR_VARIABLE JS_ERROR
)

# Print results in CMake output
message(STATUS "JavaScript Output: ${JS_OUTPUT}")
message(STATUS "JavaScript Error: ${JS_ERROR}")