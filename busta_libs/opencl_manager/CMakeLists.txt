project("BustaOpenCLManager")

include_directories(${ROOT_DIR} ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_BINARY_DIR})

include_directories("${ROOT_DIR}/others_libs/NVIDIA_SDK/OpenCL/inc")

SET(SOURCE_FILES
  ${CMAKE_CURRENT_LIST_DIR}/openclmanager.cpp
)

SET(HEADER_FILES
  ${CMAKE_CURRENT_LIST_DIR}/openclmanager.h
  ${CMAKE_CURRENT_LIST_DIR}/openclmanagerdefines.h
)

add_library(${PROJECT_NAME} STATIC
  ${SOURCE_FILES}
  ${HEADER_FILES}
)
