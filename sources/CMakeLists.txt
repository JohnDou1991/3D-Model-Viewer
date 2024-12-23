cmake_minimum_required(VERSION 3.12)

set( C_DIR ${CMAKE_CURRENT_LIST_DIR} )

subdirs(${C_DIR}/core)

set( SOURCES 
    ${C_DIR}/application.cpp 
    ${C_DIR}/main.cpp 
    ${C_DIR}/utils/filesystem/app_utils.cpp
    ${C_DIR}/objects/light/directional.cpp
    ${C_DIR}/objects/light/light.cpp
    ${C_DIR}/objects/light/point.cpp
    ${C_DIR}/objects/light/spot.cpp
    ${C_DIR}/objects/mesh.cpp
    ${C_DIR}/objects/model.cpp
    ${C_DIR}/objects/object.cpp
    ${C_DIR}/utils/vertices/color.cpp 
    ${C_DIR}/utils/vertices/normal.cpp
    ${C_DIR}/utils/vertices/position.cpp 
    ${C_DIR}/utils/vertices/texture.cpp 
    ${C_DIR}/utils/opengl/gl_utils.cpp 
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
# #add_dependencies( PROJECTX GLUT GLFW GLAD GLEW )

target_include_directories( PROJECTX PUBLIC 
    "${THIRDPARTY_DIR}/assimp/include"
    "${THIRDPARTY_DIR}/glad/include" 
    "${THIRDPARTY_DIR}/glew/include"
    "${THIRDPARTY_DIR}/glfw/include" 
    "${THIRDPARTY_DIR}/glm" 
    "${THIRDPARTY_DIR}/glm/gtc" 
    "${THIRDPARTY_DIR}/glut/include"
    "${THIRDPARTY_DIR}/stb_image/include" 

    "${C_DIR}"
)

FIND_PACKAGE(OpenGL REQUIRED)

if(APPLE)
    if( ${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm64" )
        set(MAC_SUBFOLDER "mac_arm64")
    else()
        set(MAC_SUBFOLDER "mac")
    endif()
    target_link_directories( PROJECTX PUBLIC
        "${THIRDPARTY_DIR}/glfw/lib/${MAC_SUBFOLDER}"
        "${THIRDPARTY_DIR}/glad/lib/${MAC_SUBFOLDER}"
        "${THIRDPARTY_DIR}/assimp/lib/${MAC_SUBFOLDER}"
    )
    target_link_libraries( PROJECTX "-framework GLUT" "-framework IOKit" "-framework Cocoa" glad glfw3 dl pthread ${OPENGL_gl_LIBRARY} libassimp.so CORE )

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