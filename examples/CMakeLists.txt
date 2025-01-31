link_libraries(ddengine)

set(EXAMPLES
  logger_example
  window_example
  input_example
  temporizer_example
  engine_example
  sprite_example
  renderers_example
  text_example
)

set(DATA_DESTINATION ${CMAKE_BINARY_DIR}/examples/${CMAKE_BUILD_TYPE}/data)

add_custom_target(
  copy_data ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  "${DDENGINE_ROOT_DIR}/examples/data" ${DATA_DESTINATION}
)

foreach(EXAMPLE ${EXAMPLES})
  add_executable(${EXAMPLE} "${EXAMPLE}.cpp")
  add_dependencies(${EXAMPLE} copy_data)
endforeach()