project(PROJECTX)

cmake_minimum_required(VERSION 3.12)

set(SOURCES_DIR            "${CMAKE_CURRENT_LIST_DIR}/sources" )
set(THIRDPARTY_DIR         "${CMAKE_CURRENT_LIST_DIR}/thirdparty" )
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_LIST_DIR}/bin" )

set(FREEGLUT_INSTALL_DIR "${CMAKE_CURRENT_LIST_DIR}/freeglut" )
set(GLFW_INSTALL_DIR     "${CMAKE_CURRENT_LIST_DIR}/glfw" )
set(GLAD_INSTALL_DIR     "${CMAKE_CURRENT_LIST_DIR}/glad" )
set(GLEW_INSTALL_DIR     "${CMAKE_CURRENT_LIST_DIR}/glew" )

set(CMAKE_CXX_STANDARD 11)

include( "${THIRDPARTY_DIR}/CMakeLists.txt" )
include( "${SOURCES_DIR}/CMakeLists.txt" )