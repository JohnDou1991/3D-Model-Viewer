#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#if defined(_WIN64) || defined(_WIN32)
   #define GLUT_DISABLE_ATEXIT_HACK
   #define FREEGLUT_STATIC
   #include "GL/freeglut.h"
#endif

extern float g_alpha;