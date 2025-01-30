link_libraries(ddengine)

set(EXAMPLES
  logger_example
  window_example
  input_example
)

foreach(EXAMPLE ${EXAMPLES})
  add_executable(${EXAMPLE} "${EXAMPLE}.cpp")
endforeach()