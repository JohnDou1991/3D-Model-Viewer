#include "iostream"
#include "glut.h"

using namespace std;

int main( int argc, char* argv[])
{
    glutInitWindowSize(800,600);
    glutInitWindowPosition(40,40);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutCreateWindow("FreeGLUT Shapes");
    glutMainLoop();

    return 0;
}