project("CG1")

INCLUDE_DIRECTORIES(${ROOT_DIR} ${CMAKE_CURRENT_BINARY_DIR})

#Add project files
set(QOB_SOURCES
    main.cpp
    widgets/mainwindow.cpp
    widgets/glwidget.cpp
    opengl/scene.cpp
    opengl/material.cpp
    opengl/object.cpp
    utils/options.cpp
    opengl/textures.cpp
    utils/common.cpp
    opengl/shaders.cpp
    scene/scene_tire.cpp
    scene/scene_pie.cpp
    opengl/model.cpp
    opengl/animation.cpp
    animation/animation_spin.cpp
    scene/scene_truck.cpp
    scene/scene_donut.cpp
    animation/animationshake.cpp
    scene/scene_fur.cpp
    scene/scene_bonfire.cpp
    scene/scene_voxel.cpp
    opengl/opengl.cpp
    scene/scene_obj.cpp
    cgapplication.cpp
    scene/scene_bezier.cpp
    opengl/particle_system.cpp
    opengl/particle.cpp
    utils/random.cpp
    opengl/particle_behavior.cpp
)
set(QOB_HEADERS
  widgets/mainwindow.h
  widgets/glwidget.h
  opengl/scene.h
  opengl/material.h
  opengl/object.h
  utils/options.h
  opengl/textures.h
  utils/common.h
  opengl/shaders.h
  scene/scene_tire.h
  scene/scene_pie.h
  opengl/model.h
  opengl/animation.h
  animation/animation_spin.h
  scene/scene_truck.h
  scene/scene_donut.h
  animation/animationshake.h
  scene/scene_fur.h
  scene/scene_bonfire.h
  scene/scene_voxel.h
  opengl/opengl.h
  opengl/opengl_typedef.h
  scene/scene_obj.h
  cgapplication.h
  scene/scene_bezier.h
  opengl/particle_system.h
  opengl/particle.h
  utils/random.h
  opengl/particle_behavior.h
)
set(QOB_FORMS
  widgets/mainwindow.ui
  widgets/bezier_widget.ui
  widgets/voxel_widget.ui
  widgets/particles_widget.ui
  widgets/obj_widget.ui
  widgets/fur_widget.ui
  widgets/truck_widget.ui
)
set(QOB_RESOURCES
  shaders/shaders.qrc
  resources/resources.qrc
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

#Linking Library
qt5_use_modules(${PROJECT_NAME} Core Gui Widgets OpenGL)
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${OPENGL_LIBRARIES})
