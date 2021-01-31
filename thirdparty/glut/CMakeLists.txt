project(GLUT)

cmake_minimum_required(VERSION 3.12)

set( C_DIR ${CMAKE_CURRENT_LIST_DIR} )

set(MY_URL "https://sourceforge.net/projects/freeglut/files/freeglut/3.2.1/freeglut-3.2.1.tar.gz/download?use_mirror=deac-ams&download=")
set(MY_DOWNLOAD_PATH "${C_DIR}/freeglut.tar.gz")
set(MY_EXTRACTED_FILE "${C_DIR}/")

if (NOT EXISTS "${MY_DOWNLOAD_PATH}" )
    file(DOWNLOAD "${MY_URL}" "${MY_DOWNLOAD_PATH}" 
    SHOW_PROGRESS
    STATUS status
    LOG log)
endif()

execute_process(
COMMAND ${CMAKE_COMMAND} -E tar xzf ${MY_DOWNLOAD_PATH}
WORKING_DIRECTORY ${MY_EXTRACTED_FILE}/
)

if ( EXISTS "${MY_DOWNLOAD_PATH}" )
    file(REMOVE "${MY_DOWNLOAD_PATH}")
endif()

set(GLUT_DIR ${C_DIR}/freeglut-3.2.1 )

add_subdirectory( ${GLUT_DIR} "${GLUT_DIR}/build" )