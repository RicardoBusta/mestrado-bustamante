cmake_minimum_required(VERSION 2.8)

project("mestrado-bustamante")

set(ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")

add_subdirectory("${ROOT_DIR}/libraries")
add_subdirectory("${ROOT_DIR}/third_party")
add_subdirectory("${ROOT_DIR}/prototypes")
