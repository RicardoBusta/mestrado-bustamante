cmake_minimum_required(VERSION 2.8.11)

project("mestrado-bustamante")

set(ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

FIND_PACKAGE(Qt5Widgets REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
include_directories(${Qt5Widgets_INCLUDE_DIRS})
#add_definitions(${Qt5Widgets_DEFINITIONS})

add_subdirectory("${ROOT_DIR}/libraries")
add_subdirectory("${ROOT_DIR}/third_party")
add_subdirectory("${ROOT_DIR}/prototypes")
