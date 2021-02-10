project(GLUT)

set(C_DIR ${CMAKE_CURRENT_LIST_DIR})

set(MY_URL "https://sourceforge.net/projects/freeglut/files/freeglut/3.2.1/freeglut-3.2.1.tar.gz/download?use_mirror=deac-ams&download=")

set( OPENGL_DIR "${C_DIR}/glut" )

include(ExternalProject)

ExternalProject_Add( 
    OPENGL
    PREFIX       "${OPENGL_DIR}"
    DOWNLOAD_DIR "${OPENGL_DIR}/downloads"
    STAMP_DIR    "${OPENGL_DIR}/stamp"
    LOG_DIR      "${OPENGL_DIR}/log"
    SOURCE_DIR   "${OPENGL_DIR}/src"
    BINARY_DIR   "${OPENGL_DIR}/build"
    INSTALL_DIR  "${OPENGL_DIR}/install"
    URL          "${MY_URL}"
    CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${GLUT_LIB_DIR} )