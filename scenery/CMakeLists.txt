cmake_minimum_required (VERSION 3.2)
project(scenery)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(Boost COMPONENTS system program_options REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} )
include_directories( ${GLUT_INCLUDE_DIRS} )
include_directories( ${Boost_INCLUDE_DIRS})


add_executable(scenery scenery.cpp )
target_link_libraries( scenery ${OPENGL_LIBRARY} ${GLUT_LIBRARIES} ${Boost_LIBRARIES})
