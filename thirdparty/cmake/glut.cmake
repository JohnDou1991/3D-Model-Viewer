# Download, build and install freeglut

set(FREEGLUT_URL "https://sourceforge.net/projects/freeglut/files/freeglut/3.2.1/freeglut-3.2.1.tar.gz/download?use_mirror=deac-ams&download=")
set(FREEGLUT_DIR "${TEMP_DIR}/glut")

ExternalProject_Add( 
    GLUT
    PREFIX       "${FREEGLUT_DIR}"
    DOWNLOAD_DIR "${FREEGLUT_DIR}/downloads"
    STAMP_DIR    "${FREEGLUT_DIR}/stamp"
    LOG_DIR      "${FREEGLUT_DIR}/log"
    SOURCE_DIR   "${FREEGLUT_DIR}/src"
    BINARY_DIR   "${FREEGLUT_DIR}/build"
    INSTALL_DIR  "${FREEGLUT_DIR}/install"
    URL          "${FREEGLUT_URL}"
    CMAKE_CACHE_ARGS
        -DFREEGLUT_BUILD_SHARED_LIBS:BOOL=FALSE
        -DFREEGLUT_BUILD_DEMOS:BOOL=FALSE
        -DCMAKE_INSTALL_PREFIX:PATH=${INSTALL_DIR}/glut 
)