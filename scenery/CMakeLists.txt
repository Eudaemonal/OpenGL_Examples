cmake_minimum_required (VERSION 3.2)
project(scenery)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_executable(scenery ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} scenery.cpp )
target_link_libraries( scenery ${OPENGL_LIBRARY} ${GLUT_LIBRARY} )
