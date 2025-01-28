file(GLOB_RECURSE SOURCE
  "${DDENGINE_ROOT_DIR}/src/*.cpp"
  "${DDENGINE_ROOT_DIR}/include/ddengine/*.hpp"
)

add_library(ddengine ${SOURCE})

target_include_directories(ddengine PUBLIC
  $<BUILD_INTERFACE:${DDENGINE_ROOT_DIR}/include>
)