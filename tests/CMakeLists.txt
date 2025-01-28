link_libraries(ddengine)

file(GLOB_RECURSE SOURCE "*.cpp" "*.hpp")
add_executable(test ${SOURCE})