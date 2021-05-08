# Download, build and install GLAD

set(GLAD_GIT_URL "https://github.com/Dav1dde/glad.git")
set(GLAD_DIR     "${TEMP_DIR}/glad")

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
        -DCMAKE_INSTALL_PREFIX:PATH=${INSTALL_DIR}/glad
        -DGLAD_INSTALL:BOOL=ON
)