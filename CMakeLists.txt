cmake_minimum_required(VERSION 3.12)

set(SOURCES_DIR ${CMAKE_CURRENT_LIST_DIR}/sources )

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/bin)

include( ${SOURCES_DIR}/CMakeLists.txt )