# Build example
add_executable(example
  example.cpp #file that contains the main function and the actual "application logic" for our little drawing app
)

#standard include directories for our example target
target_include_directories(example PRIVATE						   
						   ${CMAKE_SOURCE_DIR}/framework
)

target_link_libraries(example
  framework_aufgabenblatt_2 #link against our precompiled framework
  )

#define a project called "tests" which builds our 'tests' target from tests.cpp ...
add_executable(tests
  tests.cpp  #file that contains the main function and the actual "application logic" for testing
)

#and links against our framework code
target_link_libraries(tests
  framework_aufgabenblatt_2 #link against our precompiled framework
)

#standard include directories for our tests target
target_include_directories(tests PRIVATE
						   ${CMAKE_SOURCE_DIR}/framework
						   ${CMAKE_SOURCE_DIR}/external/catch2
)