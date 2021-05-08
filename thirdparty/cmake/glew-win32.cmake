# Download, build and install GLEW for Windows
# bash is mandatory!!!

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
    SOURCE_SUBDIR       "build/cmake"
    GIT_REPOSITORY      "${GLEW_GIT_URL}"
    STEP_TARGETS        download
    UPDATE_DISCONNECTED true
    CMAKE_CACHE_ARGS
        -DBUILD_UTILS:BOOL=FALSE
        -DBUILD_SHARED_LIBS:BOOL=FALSE
        -DCMAKE_INSTALL_PREFIX:PATH=${INSTALL_DIR}/glew
)

ExternalProject_Add_Step(
    GLEW
    make
    DEPENDS             GLEW-download
    COMMENT             "Call make command for GLEW..."
    COMMAND             ${PATH_TO_BASH} -c "${CMAKE_MAKE_PROGRAM} -j1 --directory=${GLEW_DIR}/src extensions"
)
ExternalProject_Add_StepTargets( GLEW make )
ExternalProject_Add_StepDependencies( GLEW configure GLEW-make )