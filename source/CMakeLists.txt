# Build example
add_executable(example
  window.cpp
  glew.c
  example.cpp)
target_link_libraries(example
  glfw
  ${GLFW_LIBRARIES}
  nanovg
  m)
add_dependencies(example glfw nanovg ${COPY_BINARY})

# Build tests
add_executable(tests
  tests.cpp)
target_link_libraries(tests
  ${GLFW_LIBRARIES})


