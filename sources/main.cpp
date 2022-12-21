#include "common.h"

#include "utils/opengl/definitions.h"
#include "utils/opengl/context.h"
#include "utils/opengl/program.h"

#include "utils/vertices.h"

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
   ShaderList shaders;
   shaders[ShaderType::VERTEX].push_back("vertex_shader");
   shaders[ShaderType::FRAGMENT].push_back("fragment_shader_orange");

   ShaderList shaders2;
   shaders2[ShaderType::VERTEX].push_back("vertex_shader");
   shaders2[ShaderType::FRAGMENT].push_back("fragment_shader_yellow");

   utils::opengl::Context context;

   {
      utils::opengl::Program program(context);
      utils::opengl::Program program2(context);

      program.LoadShaders(shaders);
      program2.LoadShaders(shaders2);

      program.LoadObject(vertices::triangle1);
      program.LoadObject(vertices::triangle2);
      program2.LoadObject(vertices::triangle3);
      program2.LoadObject(vertices::rectangle1);

      program2.LoadObject( vertices::rectangle2, vertices::indices1 );

      while ( !glfwWindowShouldClose(context.Window()) ) {
         glClear(GL_COLOR_BUFFER_BIT);

         program2.Draw();
         program.Draw();

         glfwSwapBuffers(context.Window());
         glfwPollEvents();
      };
   }

   glfwTerminate();
   return 0;
}