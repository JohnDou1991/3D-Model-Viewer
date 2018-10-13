cmake_minimum_required(VERSION 3.12)

set( C_DIR ${CMAKE_CURRENT_LIST_DIR} )

set( SOURCES ${C_DIR}/main.cpp )

add_executable( SEAFIGHT ${C_DIR}/main.cpp ${SOURCES} )