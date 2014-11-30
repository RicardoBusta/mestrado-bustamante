project("SciVis")

include_directories(${ROOT_DIR} ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_BINARY_DIR})

#include_directories("${ROOT_DIR}/others_libs/NVIDIA_SDK/OpenCL/inc")

#Add project files
set(SOURCE_FILES
  ${CMAKE_CURRENT_LIST_DIR}/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/scivis.cpp
  ${CMAKE_CURRENT_LIST_DIR}/mainwindow.cpp
  ${CMAKE_CURRENT_LIST_DIR}/scene/volumeplanesscene.cpp
  ${CMAKE_CURRENT_LIST_DIR}/scene/marchingcubesscene.cpp
  ${CMAKE_CURRENT_LIST_DIR}/data/volumedata.cpp
  ${CMAKE_CURRENT_LIST_DIR}/algorithm/marchingcubes.cpp
  ${CMAKE_CURRENT_LIST_DIR}/loadingprogress.cpp
  ${CMAKE_CURRENT_LIST_DIR}/algorithm/transferfunction.cpp
  ${CMAKE_CURRENT_LIST_DIR}/widgets/marchingcubesscenedialog.cpp
)
set(HEADER_FILES
  ${CMAKE_CURRENT_LIST_DIR}/scivis.h
  ${CMAKE_CURRENT_LIST_DIR}/mainwindow.h
  ${CMAKE_CURRENT_LIST_DIR}/scene/volumeplanesscene.h
  ${CMAKE_CURRENT_LIST_DIR}/scene/marchingcubesscene.h
  ${CMAKE_CURRENT_LIST_DIR}/data/volumedata.h
  ${CMAKE_CURRENT_LIST_DIR}/algorithm/marchingcubes.h
  ${CMAKE_CURRENT_LIST_DIR}/algorithm/marchingcubeskernel.h
  ${CMAKE_CURRENT_LIST_DIR}/loadingprogress.h
  ${CMAKE_CURRENT_LIST_DIR}/algorithm/marchingcubestables.h
  ${CMAKE_CURRENT_LIST_DIR}/algorithm/transferfunction.h
  ${CMAKE_CURRENT_LIST_DIR}/widgets/marchingcubesscenedialog.h
)
set(FORM_FILES
  ${CMAKE_CURRENT_LIST_DIR}/mainwindow.ui
  ${CMAKE_CURRENT_LIST_DIR}/loadingprogress.ui
  ${CMAKE_CURRENT_LIST_DIR}/widgets/marchingcubesscenedialog.ui
)
set(RESOURCE_FILES
)

set(OTHER_FILES
)

set(DEPENDENCY_LIBRARIES
  BustaGLWidget
  #BustaOpenCLManager
  BustaOpenGLExtensionManager
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
