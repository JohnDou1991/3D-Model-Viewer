#if defined(_WIN64) || defined(_WIN32)
    #define GLUT_DISABLE_ATEXIT_HACK
    #define FREEGLUT_STATIC
    #include "GL/freeglut.h"
#elif __linux__
    #include "GL/glut.h"
    #include "GL/freeglut_ext.h"
#endif

using namespace std;

static void display(void)
{
    glutSwapBuffers();
}

int main( int argc, char* argv[])
{
    glutInitWindowSize(800,600);
    glutInitWindowPosition(40,40);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    
    glutCreateWindow( "PROJECTX" );

    glutDisplayFunc(display);

    glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION );
    
    glutMainLoop();
    return 0;
}