link_libraries(ddengine)

file(GLOB_RECURSE logger_source "logger/*.cpp" "logger/*.hpp")
add_executable(logger ${logger_source})