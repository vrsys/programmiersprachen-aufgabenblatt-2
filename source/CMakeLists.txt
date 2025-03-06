# define the list of files required for compiling the example as well as the tests
# this list can be extended when new files relevant for the example and test application are created
set(BASE_FILES
   vec2.cpp
   vec2.hpp
   mat2.cpp
   mat2.hpp
   circle.hpp
   circle.cpp
   rectangle.cpp
   rectangle.hpp
   window.cpp # this file is responsible for creating the window
   glew.c # this file is responsible for managing OpenGL extensions and function pointers at runtime.
   Roboto-Regular_ttf_binary.h # this is the binary file of the font used by the window
)

# Build example, by including relevant BASE_FILES as well as example specific files
# Note that the example.cpp is included to define the entry point of the program
add_executable(example
  example.cpp
  ${BASE_FILES}
)

# Build tests, by including relevant BASE_FILES as well as test specific files
# Note that the tests.cpp is included to define the entry point of the program
add_executable(tests
  tests.cpp
  ${BASE_FILES}
)

target_link_libraries(example
  glfw
  ${GLFW_LIBRARIES}
  nanovg
  ${OPENGL_LIBRARIES}
  )
add_dependencies(example glfw nanovg ${COPY_BINARY})


target_link_libraries(tests
  glfw
  ${GLFW_LIBRARIES}
  nanovg
  ${OPENGL_LIBRARIES}
  )


