project("CG2")

INCLUDE_DIRECTORIES(${ROOT_DIR} ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_BINARY_DIR})

#Add project files
set(SOURCE_FILES
    main.cpp
    widgets/mainwindow.cpp 
    application.cpp 
    ray.cpp 
    constants.h
    scene/sceneobject.cpp 
    scene/scene.cpp 
    widgets/glwidget.cpp 
    widgets/raytracingwidget.cpp 
    structures.cpp 
    structures/matrix4x4.cpp 
    structures/vector.cpp 
    structures/color.cpp 
    widgets/outerviewwidget.cpp 
    structures/material.cpp 
    scene/scenelight.cpp 
    scene/triangleface.cpp 
    openclloader.cpp 
    openclraytracing.cpp 
    scene/objloader.cpp 
    scene/openglauxfunctions.cpp 
    widgets/raytracingresultviewerwidget.cpp 
    widgets/raytracingthread.cpp 
    structures/texturecontainer.cpp
)
set(HEADER_FILES
   widgets/mainwindow.h 
    application.h 
    ray.h 
    scene/sceneobject.h 
    scene/scene.h 
    widgets/glwidget.h 
    widgets/raytracingwidget.h 
    structures.h 
    structures/matrix4x4.h 
    structures/vector.h 
    structures/color.h 
    widgets/outerviewwidget.h 
    constants.h 
    structures/material.h 
    scene/scenelight.h 
    scene/triangleface.h 
    openclloader.h 
    openclloaderdefines.h 
    openclraytracing.h
    scene/objloader.h 
    scene/openglauxfunctions.h 
    widgets/raytracingresultviewerwidget.h 
    widgets/raytracingthread.h 
    structures/texturecontainer.h
)
set(FORM_FILES
    widgets/mainwindow.ui 
    widgets/raytracingresultviewerwidget.ui
)
set(RESOURCE_FILES
   resources.qrc
)
set(OTHER_FILES
    models/crystal_formations.mtl 
    models/crystal_formations.obj 
    models/cube.mtl 
    models/cube.obj 
    models/one_crystal.mtl 
    models/one_crystal.obj 
    models/car.mtl 
    models/car.obj 
    models/cubes.mtl 
    models/cubes.obj 
    models/cubes.png 
    models/spheres.obj 
    models/spheres.mtl 
    models/pyramid.obj 
    models/pyramid.mtl 
    models/environment.obj 
    models/environment.mtl 
    models/enviro_monkey.obj 
    models/enviro_monkey.mtl 
    models/enviro_ball.obj 
    models/enviro_ball.mtl 
    models/textured.obj 
    models/textured.mtl
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
  #${OTHER_FILES}
)

#Linking Library
qt5_use_modules(${PROJECT_NAME} Core Gui Widgets OpenGL)
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
