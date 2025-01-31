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
)

# Include dependencies
target_include_directories(ddengine PUBLIC
  $<BUILD_INTERFACE:${DDENGINE_ROOT_DIR}/src>
  $<BUILD_INTERFACE:${DDENGINE_ROOT_DIR}/deps/glm>
  $<BUILD_INTERFACE:${DDENGINE_ROOT_DIR}/deps/stb>
)