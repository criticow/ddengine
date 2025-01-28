file(GLOB_RECURSE SOURCE
  "${DDENGINE_ROOT_DIR}/src/*.cpp"
  "${DDENGINE_ROOT_DIR}/include/ddengine/*.hpp"
)

add_library(ddengine ${SOURCE})

# Link dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC
  glad
  glfw
)

# Include dependencies
target_include_directories(ddengine PUBLIC
  $<BUILD_INTERFACE:${DDENGINE_ROOT_DIR}/include>
  $<BUILD_INTERFACE:${NGNIA_ROOT_DIR}/deps/glm>
)