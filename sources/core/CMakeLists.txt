cmake_minimum_required(VERSION 3.12)

set( SOURCES 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/camera.cpp 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/context.cpp 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/keyboard.cpp 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/mouse.cpp 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/window.cpp 
)

add_library( CORE ${SOURCES} )

target_include_directories( CORE PUBLIC 
    "${THIRDPARTY_DIR}/glad/include" 
    "${THIRDPARTY_DIR}/glfw/include" 
    "${THIRDPARTY_DIR}/glm" 

    "${C_DIR}"
    "${C_DIR}/core"
)