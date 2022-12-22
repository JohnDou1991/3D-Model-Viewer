#include "common.h"

#include "utils/filesystem/app_utils.hpp"

#include "utils/opengl/definitions.h"
#include "utils/opengl/context.h"
#include "utils/opengl/program.h"

#include "utils/image_loader.h"

#include "utils/vertices/position.h"
#include "utils/vertices/color.h"
#include "utils/vertices/texture.h"
#include "utils/vertices/object.h"

#include "utils/vertices.h"

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
   ShaderList shaders;
   shaders[ShaderType::VERTEX].push_back("textured.vs");
   shaders[ShaderType::FRAGMENT].push_back("textured.fs");

   utils::opengl::Context context;

   utils::ImageLoader imageLoader;

   vertice::Object obj;
   obj.Add( new vertice::Position( vertices::rectangle2, 3 ));
   obj.Add( new vertice::Color( vertices::color1, 3 ));
   obj.Add( new vertice::Texture( vertices::texCoords1, 2 ));

   {
      utils::opengl::Program program(context);

      program.LoadShaders(shaders);
      program.LoadObject( obj, vertices::indices1 );
      program.LoadTexture( imageLoader.Load( utils::getCurrentDir() + "/resources/textures/texture1.jpg" ) );

      while ( !glfwWindowShouldClose(context.Window()) ) {
         glClear(GL_COLOR_BUFFER_BIT);

         program.Draw();

         glfwSwapBuffers(context.Window());
         glfwPollEvents();
      };
   }

   glfwTerminate();
   return 0;
}