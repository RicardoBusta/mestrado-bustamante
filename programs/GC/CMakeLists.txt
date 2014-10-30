project("GC")

include_directories(${ROOT_DIR} ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_BINARY_DIR})

#Add project files
set(SOURCE_FILES
    main.cpp
    rendering/scene.cpp 
    rendering/sceneobject.cpp 
    rendering/sceneconvexhull.cpp 
    rendering/scenepointcloud.cpp 
    rendering/scenetetrahedrons.cpp 
    rendering/geometry.cpp 
    rendering/scenetext.cpp 
    interface/application.cpp 
    interface/glwidget.cpp 
    interface/mainwindow.cpp 
    interface/objectcontrolwidget.cpp 
    ric.cpp 
    rendering/scenechquickhull.cpp 
    algorithm/qh_face.cpp 
    algorithm/qh_quickhull.cpp 
    rendering/qhpoly.cpp 
    rendering/scenetetradelaunay.cpp 
    rendering/deltetra.cpp
)
set(HEADER_FILES
    rendering/scene.h 
    rendering/sceneobject.h 
    rendering/sceneconvexhull.h 
    rendering/scenepointcloud.h 
    rendering/scenetetrahedrons.h 
    rendering/geometry.h 
    rendering/scenetext.h 
    interface/application.h 
    interface/glwidget.h 
    interface/mainwindow.h 
    interface/objectcontrolwidget.h 
    ric.h 
    rendering/scenechquickhull.h 
    algorithm/qh_face.h 
    algorithm/qh_quickhull.h 
    rendering/qhpoly.h 
    rendering/scenetetradelaunay.h 
    rendering/deltetra.h
)
set(FORM_FILES
    interface/mainwindow.ui 
    interface/objectcontrolwidget.ui
)
set(RESOURCE_FILES
)

set(OTHER_FILES
    HULL2D.txt 
    HULL3D.txt 
    INPUT2D.txt 
    INPUT3D.txt 
    TETRA2D.txt 
    TETRA3D.txt
    INPUT_RICARDO.txt
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
