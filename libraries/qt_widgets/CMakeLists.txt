SET(QT_WIDGETS_SOURCES test.cpp)
SET(QT_WIDGETS_HEADERS test.h)

#qt5_generate_moc(test.cpp main.moc)
#qt5_wrap_cpp

#add_executable(helloworld test.cpp main.moc)

#target_link_libraries(helloworld Qt5::Widgets)

#All objects that include Q_OBJECT must be listed here to be run by MOC
