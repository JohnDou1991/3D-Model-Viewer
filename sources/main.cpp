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
   obj.Add( new vertice::Position( vertices::cube1, 3 ));
   // obj.Add( new vertice::Color( vertices::color1, 3 ));
   obj.Add( new vertice::Texture( vertices::cube1_tex_coords, 2 ));

   {
      utils::opengl::Program program(context);
      // utils::opengl::Program program2(context);

      {
         const auto& texture1 = imageLoader.Load( utils::getCurrentDir() + "/resources/textures/texture1.jpg" );

         program.LoadShaders(shaders);
         program.LoadObject( obj );
         program.LoadTexture( texture1 );

         program.LoadTransformation( [](GLuint program)
         {
            glm::mat4 model = glm::mat4(1);
            model = glm::rotate(model, (float)glfwGetTime() + glm::radians(0.0f), glm::vec3( 0.25, 1.0, 0.0 ));
            glUniformMatrix4fv( glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model) );

            glm::mat4 view = glm::mat4(1);
            view = glm::translate(view, glm::vec3( 0, 0, -5));
            glUniformMatrix4fv( glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view) );

            glm::mat4 projection = glm::mat4(1);
            projection = glm::perspective( glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f );
            glUniformMatrix4fv( glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection) );
         });
      }

      int frame = 0;

      while ( !glfwWindowShouldClose(context.Window()) ) {
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         program.Draw();

         glfwSwapBuffers(context.Window());
         glfwPollEvents();
      };
   }

   glfwTerminate();
   return 0;
}