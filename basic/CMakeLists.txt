cmake_minimum_required (VERSION 3.2)
project(test01)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_executable(test01 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} test01.cpp)
target_link_libraries( test01 ${OPENGL_LIBRARY} ${GLUT_LIBRARY} )
