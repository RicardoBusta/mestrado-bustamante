project("SciVis")

include_directories(${ROOT_DIR} ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_BINARY_DIR})

#Add project files
set(SOURCE_FILES
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/mainwindow.cpp
  ${CMAKE_CURRENT_LIST_DIR}/scene/volumeplanesscene.cpp
  ${CMAKE_CURRENT_LIST_DIR}/data/volumedata.cpp
  ${CMAKE_CURRENT_LIST_DIR}/algorithm/marchingcubes.cpp
)
set(HEADER_FILES
  ${CMAKE_CURRENT_LIST_DIR}/mainwindow.h
  ${CMAKE_CURRENT_LIST_DIR}/scene/volumeplanesscene.h
  ${CMAKE_CURRENT_LIST_DIR}/data/volumedata.h
  ${CMAKE_CURRENT_LIST_DIR}/algorithm/marchingcubes.h
)
set(FORM_FILES
  ${CMAKE_CURRENT_LIST_DIR}/mainwindow.ui
)
set(RESOURCE_FILES

)

set(OTHER_FILES
)

set(DEPENDENCY_LIBRARIES
  BustaGLWidget
)

#Qt steps before compiling
qt5_wrap_cpp(HEADER_FILES_MOC ${HEADER_FILES})
qt5_wrap_ui(FORM_HEADERS ${FORM_FILES})
qt5_add_resources(RESOURCE_FILES_RCC ${RESOURCE_FILES})

#Adding files post-qt to project
add_executable(${PROJECT_NAME}
  ${SOURCE_FILES}
  ${HEADER_FILES_MOC}
  ${FORM_HEADERS}
  ${RESOURCE_FILES_RCC}
)

#Linking Library
qt5_use_modules(${PROJECT_NAME} Core Gui Widgets OpenGL)
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${DEPENDENCY_LIBRARIES})
