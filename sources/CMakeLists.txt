cmake_minimum_required(VERSION 3.12)

set( C_DIR ${CMAKE_CURRENT_LIST_DIR} )

set( SOURCES 
    ${C_DIR}/main.cpp 
    ${C_DIR}/utils/filesystem/app_utils.cpp
    ${C_DIR}/objects/light/directional.cpp
    ${C_DIR}/objects/light/light.cpp
    ${C_DIR}/objects/light/point.cpp
    ${C_DIR}/objects/light/spot.cpp
    ${C_DIR}/objects/mesh.cpp
    ${C_DIR}/objects/model.cpp
    ${C_DIR}/utils/vertices/color.cpp 
    ${C_DIR}/utils/vertices/normal.cpp 
    ${C_DIR}/utils/vertices/object.cpp
    ${C_DIR}/utils/vertices/position.cpp 
    ${C_DIR}/utils/vertices/texture.cpp 
    ${C_DIR}/utils/opengl/gl_utils.cpp 
    ${C_DIR}/utils/opengl/camera.cpp 
    ${C_DIR}/utils/opengl/context.cpp 
    ${C_DIR}/utils/opengl/observers/keyboard.cpp 
    ${C_DIR}/utils/opengl/observers/mouse.cpp 
    ${C_DIR}/utils/opengl/program.cpp 
    ${C_DIR}/utils/image_loader.cpp 
)

if(APPLE)
    set( SOURCES ${SOURCES} ${C_DIR}/utils/filesystem/mac/app_utils.cpp )
elseif(UNIX)
    set( SOURCES ${SOURCES} ${C_DIR}/utils/filesystem/unix/app_utils.cpp )
elseif(WIN32)
    set( SOURCES ${SOURCES} ${C_DIR}/utils/filesystem/win/app_utils.cpp )
endif()

add_executable( PROJECTX ${C_DIR}/main.cpp ${SOURCES} )
#add_dependencies( PROJECTX GLUT GLFW GLAD GLEW )

target_include_directories( PROJECTX PUBLIC 
    "${THIRDPARTY_DIR}/glut/include" 
    "${THIRDPARTY_DIR}/glfw/include" 
    "${THIRDPARTY_DIR}/glad/include" 
    "${THIRDPARTY_DIR}/glew/include"
    "${THIRDPARTY_DIR}/assimp/include"

    "${C_DIR}"
    "${C_DIR}/include"
    "${C_DIR}/include/glm" 
)

FIND_PACKAGE(OpenGL REQUIRED)

if(APPLE)

    target_link_directories( PROJECTX PUBLIC
        "${THIRDPARTY_DIR}/glfw/lib/mac"
        "${THIRDPARTY_DIR}/glad/lib/mac"
        "${THIRDPARTY_DIR}/assimp/lib/mac"
    )
    target_link_libraries( PROJECTX "-framework GLUT" "-framework IOKit" "-framework Cocoa" glad glfw3 dl pthread ${OPENGL_gl_LIBRARY} libassimp.so )

elseif(UNIX)

    target_link_directories( PROJECTX PUBLIC 
        "${THIRDPARTY_DIR}/glut/lib/linux"
        "${THIRDPARTY_DIR}/glfw/lib/linux"
        "${THIRDPARTY_DIR}/glad/lib/linux"
        "${THIRDPARTY_DIR}/glew/lib/linux"
        "${THIRDPARTY_DIR}/assimp/lib/linux"
    )

    FIND_PACKAGE(X11 REQUIRED)
    target_link_libraries( PROJECTX ${X11_X11_LIB} ${X11_Xxf86vm_LIB} ${X11_Xinput_LIB} )    

elseif(WIN32)
    target_link_libraries( PROJECTX freeglut_static glfw3 glew32.a ${OPENGL_gl_LIBRARY} winmm )
endif()

add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${C_DIR}/shaders
                ${EXECUTABLE_OUTPUT_PATH}/resources/shaders )

add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${C_DIR}/textures
                ${EXECUTABLE_OUTPUT_PATH}/resources/textures )

add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${C_DIR}/models
                ${EXECUTABLE_OUTPUT_PATH}/resources/models )