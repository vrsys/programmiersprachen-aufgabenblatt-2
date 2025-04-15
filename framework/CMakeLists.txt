#the majority of the files you are going to edit for task A2
set(FRAMEWORK_DATA_TYPE_FILES
	circle.hpp
	circle.cpp
	color.hpp
	color.cpp
	mat2.hpp
	mat2.cpp
	rectangle.hpp
	rectangle.cpp
	vec2.hpp
	vec2.cpp
	window.hpp
	window.cpp
)

#glew contains resolved function pointers to OpenGL calls
set(GL_RELATED_COMPILEABLE_DEPENDENCIES 
    glew.c
)

set(GLFW_VERSION_DEPENDENT_DIRECTORY glfw-3.4)
set(FULL_GLFW_INCLUDE_DIRECTORY ${CMAKE_SOURCE_DIR}/external/${GLFW_VERSION_DEPENDENT_DIRECTORY}/include)
#include_directories(${FULL_GLFW_INCLUDE_DIRECTORY})


#first we build a library (c.a. collection of reusable classes) from our files
add_library(framework_aufgabenblatt_2 STATIC ${FRAMEWORK_DATA_TYPE_FILES} ${GL_RELATED_COMPILEABLE_DEPENDENCIES})
target_include_directories(framework_aufgabenblatt_2 PRIVATE 
						   ${FULL_GLFW_INCLUDE_DIRECTORY} 
						   ${CMAKE_SOURCE_DIR}/external/binarized_fonts
						   ${CMAKE_SOURCE_DIR}/external/nanovg/src
						   ${CMAKE_SOURCE_DIR}/external/binarized_fonts
)

target_link_libraries(framework_aufgabenblatt_2   
	glfw
	${GLFW_LIBRARIES}
	nanovg
	${OPENGL_LIBRARIES}
)


