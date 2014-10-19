project("BustaOpenGLExtensionManager")

SET(SOURCE_FILES
  ${CMAKE_CURRENT_LIST_DIR}/openglextensionmanager.cpp
)

SET(HEADER_FILES
  ${CMAKE_CURRENT_LIST_DIR}/openglextensionmanager.h
)

add_library(${PROJECT_NAME} STATIC
  ${SOURCE_FILES}
  ${HEADER_FILES}
)
