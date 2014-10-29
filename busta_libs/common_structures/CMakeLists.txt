project("BustaCommonStructures")


SET(SOURCE_FILES
  ${CMAKE_CURRENT_LIST_DIR}/matrix4x4.cpp
  ${CMAKE_CURRENT_LIST_DIR}/vector4.cpp
)

SET(HEADER_FILES
  ${CMAKE_CURRENT_LIST_DIR}/matrix4x4.h
  ${CMAKE_CURRENT_LIST_DIR}/vector4.h
)

add_library(${PROJECT_NAME} STATIC
  ${SOURCE_FILES}
  ${HEADER_FILES}
)
