project(GLUT)

set(C_DIR ${CMAKE_CURRENT_LIST_DIR})

set(FREEGLUT_URL "https://sourceforge.net/projects/freeglut/files/freeglut/3.2.1/freeglut-3.2.1.tar.gz/download?use_mirror=deac-ams&download=")
set(FREEGLUT_DIR "${C_DIR}/freeglut")

set(GLFW_GIT_URL "https://github.com/glfw/glfw.git")
set(GLFW_DIR     "${C_DIR}/glfw")

set(GLAD_GIT_URL "https://github.com/Dav1dde/glad.git")
set(GLAD_DIR     "${C_DIR}/glad")

set(GLEW_GIT_URL "https://github.com/nigels-com/glew.git")
set(GLEW_DIR     "${C_DIR}/glew")

include(ExternalProject)

ExternalProject_Add( 
    FREEGLUT
    PREFIX       "${FREEGLUT_DIR}"
    DOWNLOAD_DIR "${FREEGLUT_DIR}/downloads"
    STAMP_DIR    "${FREEGLUT_DIR}/stamp"
    LOG_DIR      "${FREEGLUT_DIR}/log"
    SOURCE_DIR   "${FREEGLUT_DIR}/src"
    BINARY_DIR   "${FREEGLUT_DIR}/build"
    INSTALL_DIR  "${FREEGLUT_DIR}/install"
    URL          "${FREEGLUT_URL}"
    CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${FREEGLUT_INSTALL_DIR} )

ExternalProject_Add(
    GLFW
    PREFIX         "${GLFW_DIR}"
    STAMP_DIR      "${GLFW_DIR}/stamp"
    LOG_DIR        "${GLFW_DIR}/log"
    SOURCE_DIR     "${GLFW_DIR}/src"
    BINARY_DIR     "${GLFW_DIR}/build"
    INSTALL_DIR    "${GLFW_DIR}/install"
    GIT_REPOSITORY "${GLFW_GIT_URL}"
    UPDATE_DISCONNECTED true
    CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${GLFW_INSTALL_DIR}
)

ExternalProject_Add(
    GLAD
    PREFIX         "${GLAD_DIR}"
    STAMP_DIR      "${GLAD_DIR}/stamp"
    LOG_DIR        "${GLAD_DIR}/log"
    SOURCE_DIR     "${GLAD_DIR}/src"
    BINARY_DIR     "${GLAD_DIR}/build"
    INSTALL_DIR    "${GLAD_DIR}/install"
    GIT_REPOSITORY "${GLAD_GIT_URL}"
    UPDATE_DISCONNECTED true
    CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${GLAD_INSTALL_DIR}
        -DGLAD_INSTALL:BOOL=ON
)

ExternalProject_Add(
    GLEW
    PREFIX              "${GLEW_DIR}"
    STAMP_DIR           "${GLEW_DIR}/stamp"
    LOG_DIR             "${GLEW_DIR}/log"
    SOURCE_DIR          "${GLEW_DIR}/src"
    BINARY_DIR          "${GLEW_DIR}/build"
    INSTALL_DIR         "${GLEW_DIR}/install"
    GIT_REPOSITORY      "${GLEW_GIT_URL}"
    UPDATE_DISCONNECTED true
    CONFIGURE_COMMAND   make --directory=${GLEW_DIR}/src extensions
    COMMAND             cmake ${GLEW_DIR}/src/build/cmake -DCMAKE_INSTALL_PREFIX:PATH=${GLEW_INSTALL_DIR}
)