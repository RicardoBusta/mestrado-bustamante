project("SpaceView")

include_directories(${ROOT_DIR} ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_BINARY_DIR})

#Add project files
set(SOURCE_FILES
  main.cpp
  mainwindow.cpp
  glwidget.cpp
  scene.cpp
  object.cpp
  opengl/textures.cpp
  opengl/model.cpp
  opengl/material.cpp
  opengl/common.cpp
  space3d.cpp
  slidepage.cpp
  space_bodies/sun.cpp
  space_bodies/earth.cpp
  space_bodies/moon.cpp
  space_bodies/solarsystem.cpp
  space_bodies/mercury.cpp
  space_bodies/venus.cpp
  space_bodies/mars.cpp
  space_bodies/jupiter.cpp
  space_bodies/saturn.cpp
  space_bodies/neptune.cpp
  space_bodies/uranus.cpp
  space_bodies/pluto.cpp
)
set(HEADER_FILES
  mainwindow.h
  glwidget.h
  scene.h
  object.h
  opengl/textures.h
  opengl/model.h
  opengl/material.h
  opengl/common.h
  space3d.h
  slidepage.h
  space_bodies/sun.h
  space_bodies/earth.h
  space_bodies/moon.h
  space_bodies/solarsystem.h
  space_bodies/mercury.h
  space_bodies/venus.h
  space_bodies/mars.h
  space_bodies/jupiter.h
  space_bodies/saturn.h
  space_bodies/neptune.h
  space_bodies/uranus.h
  space_bodies/pluto.h
)
set(FORM_FILES
  mainwindow.ui
)
set(RESOURCE_FILES
  models/Models.qrc
  textures/Textures.qrc
)

set(OTHER_FILES
)

set(DEPENDENCY_LIBRARIES

)

#Qt steps before compiling
qt5_wrap_cpp(HEADER_FILES_MOC ${HEADER_FILES})
qt5_wrap_ui(FORM_HEADERS ${FORM_FILES})
qt5_add_resources(RESOURCE_FILES_RCC ${RESOURCE_FILES})

#Adding files post-qt to project
add_executable(${PROJECT_NAME}
  ${SOURCE_FILES}
  ${HEADER_FILES_MOC}
  ${HEADER_FILES}
  ${FORM_HEADERS}
  ${RESOURCE_FILES_RCC}
  ${OTHER_FILES}
)

#Linking Library
qt5_use_modules(${PROJECT_NAME} Core Gui Widgets OpenGL)
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${OPENGL_LIBRARIES} ${DEPENDENCY_LIBRARIES})
