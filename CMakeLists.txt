cmake_minimum_required(VERSION 3.14)
project(Aufgabenblatt_2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenGL REQUIRED)

# Add externals
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)
add_definitions(-DGLEW_STATIC)

# build GLFW
set(GLFW_DIRECTORY glfw-3.2.1)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_DIRECTORY}/include)

set(GLFW_INSTALL OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE STRING "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_DIRECTORY})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_DIRECTORY}/include)

set(NANOVG_DIRECTORY nanovg)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/src)

add_library(nanovg STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/src/nanovg.c
)

# Quench warnings while compiling NanoVG
if (CMAKE_COMPILER_IS_GNUCC)
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/src/nanovg.c PROPERTIES COMPILE_FLAGS -Wno-unused-result)
elseif(MSVC)
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/src/nanovg.c PROPERTIES COMPILE_FLAGS "/wd4005 /wd4456 /wd4457")
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/example/Roboto-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/example/Roboto-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/source/)

if(MSVC)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/example/Roboto-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/source/Debug)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/example/Roboto-Regular.ttf DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/source/Release)
endif(MSVC)

# Use catch for testing
set(CATCH_DIRECTORY catch2)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/${CATCH_DIRECTORY})

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

add_subdirectory(source)
