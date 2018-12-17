cmake_minimum_required (VERSION 3.2)
project(basic)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_executable(basic ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} basic.cpp)
target_link_libraries( basic ${OPENGL_LIBRARY} ${GLUT_LIBRARY} )
