project("BustaGLWidget")

include_directories(${ROOT_DIR} ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_BINARY_DIR})

SET(SOURCE_FILES
  ${CMAKE_CURRENT_LIST_DIR}/glwidget.cpp
  ${CMAKE_CURRENT_LIST_DIR}/glwidgetscene.cpp
)
SET(HEADER_FILES
  ${CMAKE_CURRENT_LIST_DIR}/glwidget.h
  ${CMAKE_CURRENT_LIST_DIR}/glwidgetscene.h
)

#Qt steps before compiling
qt5_wrap_cpp(HEADER_FILES_MOC ${HEADER_FILES})
qt5_wrap_ui(FORM_HEADERS ${FORM_FILES})
qt5_add_resources(RESOURCE_FILES_RCC ${RESOURCE_FILES})

#Adding files post-qt to project
add_library(${PROJECT_NAME} STATIC
  ${SOURCE_FILES}
  ${HEADER_FILES_MOC}
  ${FORM_HEADERS}
  ${RESOURCE_FILES_RCC}
)

#Linking Library
qt5_use_modules(${PROJECT_NAME} Core Gui Widgets OpenGL)
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
