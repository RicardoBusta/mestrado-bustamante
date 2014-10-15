cmake_minimum_required(VERSION 2.8.11)
cmake_policy(SET CMP0043 NEW)

project("mestrado-bustamante")

set(ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

#The flag -DCMAKE_PREFIX_PATH=C:\Qt\5.*\ must be defined
if(DEFINED CMAKE_PREFIX_PATH)
    message(STATUS "CMAKE_PREFIX_PATH set to ${CMAKE_PREFIX_PATH}")
else()
    message(WARNING "CMAKE_PREFIX_PATH not set.")
endif()

FIND_PACKAGE(Qt5Widgets REQUIRED)
message(STATUS "Qt5Widgets found.")
FIND_PACKAGE(Qt5Opengl REQUIRED)
message(STATUS "Qt5Opengl found.")
FIND_PACKAGE(OpenGL REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
include_directories(${Qt5Widgets_INCLUDE_DIRS})
#add_definitions(${Qt5Widgets_DEFINITIONS})

add_subdirectory("${ROOT_DIR}/busta_libs")
add_subdirectory("${ROOT_DIR}/others_libs")
add_subdirectory("${ROOT_DIR}/prototypes")
add_subdirectory("${ROOT_DIR}/programs")
