# Download, build and install GLFW

set(GLFW_GIT_URL "https://github.com/glfw/glfw.git")
set(GLFW_DIR     "${TEMP_DIR}/glfw")

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
        -DCMAKE_INSTALL_PREFIX:PATH=${INSTALL_DIR}/glfw
        -DGLFW_BUILD_EXAMPLES:BOOL=FALSE
        -DGLFW_BUILD_TESTS:BOOL=FALSE
        -DGLFW_BUILD_DOCS:BOOL=FALSE
)