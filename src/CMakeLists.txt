file(GLOB_RECURSE SOURCE
  "${DDENGINE_ROOT_DIR}/src/*.cpp"
  "${DDENGINE_ROOT_DIR}/src/*.hpp"
)

add_library(ddengine ${SOURCE})

target_precompile_headers(ddengine PRIVATE ddenginepch.hpp)

# Link dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC
  glad
  glfw
  tinyxml2
  freetype
)

# Include dependencies
target_include_directories(ddengine PUBLIC
  $<BUILD_INTERFACE:${DDENGINE_ROOT_DIR}/include>
  $<BUILD_INTERFACE:${DDENGINE_ROOT_DIR}/deps/glm>
  $<BUILD_INTERFACE:${DDENGINE_ROOT_DIR}/deps/stb>
  $<BUILD_INTERFACE:${DDENGINE_ROOT_DIR}/deps/tinyxml2>
  $<BUILD_INTERFACE:${DDENGINE_ROOT_DIR}/deps/rapidjson/include>
)