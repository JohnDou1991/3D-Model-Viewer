cmake_minimum_required(VERSION 3.12)

set( SOURCES 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/camera.cpp 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/object.cpp 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/scene.cpp 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/shader_base.cpp 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/shader_manager.cpp 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/texture.cpp 
   ${CMAKE_CURRENT_LIST_DIR}/src/opengl/texture_manager.cpp 
)

add_library( CORE ${SOURCES} )

target_include_directories( CORE PUBLIC 
    "${THIRDPARTY_DIR}/glad/include" 
    "${THIRDPARTY_DIR}/glfw/include" 
    "${THIRDPARTY_DIR}/glm" 

    "${C_DIR}"
    "${C_DIR}/core"
    "${C_DIR}/core/context"
    "${C_DIR}/core/input"
)

add_subdirectory(context)
add_subdirectory(input)

target_link_libraries(CORE CONTEXT)