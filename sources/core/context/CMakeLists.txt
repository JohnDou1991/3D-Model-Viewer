cmake_minimum_required(VERSION 3.12)

set( SOURCES 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/context.cpp 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/window.cpp 
)

add_library(CONTEXT ${SOURCES})

target_include_directories(CONTEXT PUBLIC  
    "${THIRDPARTY_DIR}/glad/include" 
    "${THIRDPARTY_DIR}/glfw/include"
    "${C_DIR}"
    "${C_DIR}/core/context"
    "${C_DIR}/core/input"
)

target_link_libraries(CONTEXT INPUT glad)