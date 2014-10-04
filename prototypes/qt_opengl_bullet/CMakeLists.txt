project("qt_opengl_bullet")

#Add project files
set(QOB_SOURCES
  main.cpp
  mainwindow.cpp
)
set(QOB_HEADERS
  mainwindow.h
)
set(QOB_FORMS
 mainwindow.ui
)
set(QOB_RESOURCES
)

#Qt steps before compiling
qt5_wrap_cpp(QOB_HEADERS_MOC ${QOB_HEADERS})
qt5_wrap_ui(QOB_FORMS_HEADERS ${QOB_FORMS})
qt5_add_resources(QOB_RESOURCES_RCC ${QOB_RESOURCES})

#Adding files post-qt to project
add_executable(${PROJECT_NAME}
  ${QOB_SOURCES}
  ${QOB_HEADERS_MOC}
  ${QOB_FORMS_HEADERS}
  ${QOB_RESOURCES_RCC}
)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

#Linking Library
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
