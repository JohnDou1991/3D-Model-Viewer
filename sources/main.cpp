
#include "application.hpp"

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
   Application app;
   app.Init();
   app.LoadShaders();
   app.Start();
   return 0;
}