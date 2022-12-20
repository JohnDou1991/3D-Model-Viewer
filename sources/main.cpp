#include "common.h"

#include "utils/opengl/definitions.h"
#include "utils/opengl/program.h"

#include "utils/vertices.h"

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
   ShaderList shaders;
   shaders[ShaderType::VERTEX].push_back("vertex_shader");
   shaders[ShaderType::FRAGMENT].push_back("fragment_shader");

   utils::opengl::Program program(vertices::rectangle1);

   program.LoadShaders(shaders);
   program.InitBuffers();

   while ( !glfwWindowShouldClose(program.context().Window()) )
   {
      glClear(GL_COLOR_BUFFER_BIT);

      program.Draw();

      glfwSwapBuffers(program.context().Window());
      glfwPollEvents();
   }

   glfwTerminate();
   return 0;
}