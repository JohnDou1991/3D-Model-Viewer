# Download, build and install GLEW for Linux

set(GLEW_GIT_URL "https://github.com/nigels-com/glew.git")
set(GLEW_DIR     "${TEMP_DIR}/glew")

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
    COMMAND             cmake ${GLEW_DIR}/src/build/cmake -DCMAKE_INSTALL_PREFIX:PATH=${INSTALL_DIR}/glew
    CMAKE_CACHE_ARGS
        -DBUILD_UTILS:BOOL=FALSE
        -DBUILD_SHARED_LIBS:BOOL=FALSE
)