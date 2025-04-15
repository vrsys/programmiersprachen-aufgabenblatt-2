cmake_minimum_required(VERSION 3.14)
project(Aufgabenblatt_2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenGL REQUIRED)

# Add externals
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external)
add_definitions(-DGLEW_STATIC)

# build GLFW
set(GLFW_VERSION_DEPENDENT_DIRECTORY glfw-3.4)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/${GLFW_VERSION_DEPENDENT_DIRECTORY})


# compile nanovg from source
add_library(nanovg STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/external/nanovg/src/nanovg.c
)

# Quench warnings while compiling NanoVG
if (CMAKE_COMPILER_IS_GNUCC)
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/src/nanovg.c PROPERTIES COMPILE_FLAGS -Wno-unused-result)
elseif(MSVC)
  set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/external/${NANOVG_DIRECTORY}/src/nanovg.c PROPERTIES COMPILE_FLAGS "/wd4005 /wd4456 /wd4457")
endif()


if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

add_subdirectory(framework)
add_subdirectory(applications)
