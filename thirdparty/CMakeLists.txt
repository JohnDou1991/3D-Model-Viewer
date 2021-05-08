project(GLUT)

set( TEMP_DIR ${CMAKE_CURRENT_LIST_DIR}/temp )
set( INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/static ) #TODO support shared in future

include( ExternalProject )

include( "${CMAKE_CURRENT_LIST_DIR}/cmake/glut.cmake" )
include( "${CMAKE_CURRENT_LIST_DIR}/cmake/glfw.cmake" )
include( "${CMAKE_CURRENT_LIST_DIR}/cmake/glad.cmake" )

if(WIN32)
    set( PATH_TO_BASH "C:/Program Files/Git/git-bash.exe" ) #this is mandatory TODO find more sophisticated way
    include( "${CMAKE_CURRENT_LIST_DIR}/cmake/glew-win32.cmake" )
elseif(UNIX)
    include( "${CMAKE_CURRENT_LIST_DIR}/cmake/glew-linux.cmake" )
endif()