project(PROJECTX)

cmake_minimum_required(VERSION 3.12)

set(SOURCES_DIR            "${CMAKE_CURRENT_LIST_DIR}/sources" )
set(THIRDPARTY_DIR         "${CMAKE_CURRENT_LIST_DIR}/thirdparty" )
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_LIST_DIR}/bin" )

set(CMAKE_CXX_STANDARD 11)

#include( "${THIRDPARTY_DIR}/CMakeLists.txt" ) // TODO Remove this and use precompiled 3rd parties instead of sub projects
include( "${SOURCES_DIR}/CMakeLists.txt" )