cmake_minimum_required(VERSION 3.12)

set( C_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCES ${C_DIR}/main.cpp )

if(UNIX)
    set( SOURCES ${SOURCES} ${C_DIR}/utils/filesystem/unix/app_utils.cpp )
elseif(WIN32)
    set( SOURCES ${SOURCES} ${C_DIR}/utils/filesystem/win/app_utils.cpp )
endif()

add_executable( PROJECTX ${C_DIR}/main.cpp ${SOURCES} )
add_dependencies( PROJECTX GLUT GLFW GLAD GLEW )

target_include_directories( PROJECTX PUBLIC 
    "${INSTALL_DIR}/glut/include" 
    "${INSTALL_DIR}/glfw/include" 
    "${INSTALL_DIR}/glad/include" 
    "${INSTALL_DIR}/glew/include"

    "${C_DIR}" 
)

target_link_directories( PROJECTX PUBLIC 
    "${INSTALL_DIR}/glut/lib" 
    "${INSTALL_DIR}/glfw/lib" 
    "${INSTALL_DIR}/glad/lib" 
    "${INSTALL_DIR}/glew/lib" 
)

FIND_PACKAGE(OpenGL REQUIRED)

if(UNIX)
    FIND_PACKAGE(X11 REQUIRED)
    target_link_libraries( PROJECTX glut glfw3 glad dl pthread GLEW.a GL ${OPENGL_gl_LIBRARY} ${X11_X11_LIB} ${X11_Xxf86vm_LIB} ${X11_Xinput_LIB} )
elseif(WIN32)
    target_link_libraries( PROJECTX freeglut_static glfw3 glew32.a ${OPENGL_gl_LIBRARY} winmm )
endif()

add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${C_DIR}/shaders
                ${EXECUTABLE_OUTPUT_PATH}/resources/shaders )