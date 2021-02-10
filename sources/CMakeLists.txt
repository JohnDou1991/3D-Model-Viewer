cmake_minimum_required(VERSION 3.12)

set( C_DIR ${CMAKE_CURRENT_LIST_DIR} )
set( SOURCES ${C_DIR}/main.cpp  )

add_executable( PROJECTX ${C_DIR}/main.cpp ${SOURCES} )
add_dependencies( PROJECTX OPENGL )

target_include_directories( PROJECTX PUBLIC "${GLUT_LIB_DIR}/include" )
target_link_directories( PROJECTX PUBLIC "${GLUT_LIB_DIR}/lib" )

FIND_PACKAGE(OpenGL REQUIRED)

if(UNIX)
    FIND_PACKAGE(X11 REQUIRED)
    target_link_libraries( PROJECTX libglut.a ${OPENGL_gl_LIBRARY} ${X11_X11_LIB} ${X11_Xxf86vm_LIB} ${X11_Xinput_LIB} )
else()
    target_link_libraries( PROJECTX freeglut_static ${OPENGL_gl_LIBRARY} winmm )
endif()