cmake_minimum_required(VERSION 3.12)

set( C_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCES ${C_DIR}/main.cpp )

add_executable( PROJECTX ${C_DIR}/main.cpp ${SOURCES} )
add_dependencies( PROJECTX FREEGLUT GLFW GLAD GLEW )

target_include_directories( PROJECTX PUBLIC "${FREEGLUT_INSTALL_DIR}/include" "${GLFW_INSTALL_DIR}/include" "${GLAD_INSTALL_DIR}/include" "${GLEW_INSTALL_DIR}/include" )
target_link_directories( PROJECTX PUBLIC "${FREEGLUT_INSTALL_DIR}/lib" "${GLFW_INSTALL_DIR}/lib" "${GLAD_INSTALL_DIR}/lib" "${GLEW_INSTALL_DIR}/lib" )

FIND_PACKAGE(OpenGL REQUIRED)

if(UNIX)
    FIND_PACKAGE(X11 REQUIRED)
    target_link_libraries( PROJECTX glut glfw3 glad dl pthread GLEW.a ${OPENGL_gl_LIBRARY} ${X11_X11_LIB} ${X11_Xxf86vm_LIB} ${X11_Xinput_LIB} )
else()
    target_link_libraries( PROJECTX freeglut_static ${OPENGL_gl_LIBRARY} winmm )
endif()