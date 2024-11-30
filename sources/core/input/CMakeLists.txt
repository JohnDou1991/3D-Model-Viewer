cmake_minimum_required(VERSION 3.12)

set( SOURCES 
   ${CMAKE_CURRENT_LIST_DIR}/src/glfw/keyboard.cpp 
   ${CMAKE_CURRENT_LIST_DIR}/src/glfw/mouse.cpp 
)

add_library(INPUT ${SOURCES})

target_include_directories( INPUT PUBLIC  
    "${THIRDPARTY_DIR}/glfw/include"
    "${C_DIR}/core/input"
)

target_link_libraries(INPUT glfw3)