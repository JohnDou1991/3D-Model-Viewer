#include "common.h"

#include "utils/filesystem/app_utils.hpp"

#include "utils/opengl/definitions.h"
#include "utils/opengl/context.h"
#include "utils/opengl/camera.hpp"
#include "utils/opengl/program.h"

#include "utils/image_loader.h"


#include "utils/vertices/color.h"
#include "utils/vertices/normal.h"
#include "utils/vertices/object.h"
#include "utils/vertices/position.h"
#include "utils/vertices/texture.h"

#include "utils/vertices.h"

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
   utils::opengl::Context context;

   ShaderList shadersObject;
   shadersObject[ShaderType::VERTEX].push_back("light.vs");
   shadersObject[ShaderType::FRAGMENT].push_back("lightObject.fs");

   ShaderList shadersLight;
   shadersLight[ShaderType::VERTEX].push_back("light.vs");
   shadersLight[ShaderType::FRAGMENT].push_back("lightSource.fs");

   vertice::Object obj;
   obj.Add( new vertice::Position( vertices::cube1, 3 ));
   obj.Add( new vertice::Normal( vertices::cube1_normals, 3 ));
   obj.Add( new vertice::Texture( vertices::cube1_tex_coords, 2 ));

   utils::Image texture = utils::ImageLoader().Load( utils::getCurrentDir() + "/resources/textures/texture1.jpg" );

   {
      std::vector<utils::opengl::Program> programs;

      auto addObject = [&programs, &context]( 
         const ShaderList& shaders
       , const vertice::Object& obj
       , const utils::Image& texture ) -> utils::opengl::Program&
      {
         programs.emplace_back(context);
         utils::opengl::Program& program = programs.back();

         program.LoadShaders( shaders );
         program.LoadObject( obj );
         program.LoadTexture( texture );

         return program;
      };

      glm::vec3 lightPosition( 1, 1, -2 );
      const glm::vec3 c_lPos = lightPosition;

      // object 1
      {
         auto& program = addObject( shadersObject, obj, texture );

         program.LoadTransformation( [&lightPosition, &context](GLuint program)
         {
            glm::mat4 model = glm::mat4(1);
            model = glm::rotate(model, (float)glfwGetTime()/10 + glm::radians(45.0f), glm::vec3( 0.0, 10.0, 20.0 ));
            glUniformMatrix4fv( glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model) );

            glm::mat4 view = glm::mat4(1);
            view = context.GetCamera().LookAt();
            glUniformMatrix4fv( glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view) );

            glm::mat4 projection = glm::mat4(1);
            projection = glm::perspective( glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f );
            glUniformMatrix4fv( glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection) );

            glUniform3fv( glGetUniformLocation(program, "objectColor"), 1, glm::value_ptr( glm::vec3( 1.0, 0.5, 0.31 )) );
            glUniform3fv( glGetUniformLocation(program, "lightColor"), 1, glm::value_ptr( glm::vec3( 1.0, 1.0, 1.0 )) );

            glUniform3fv( glGetUniformLocation(program, "lightPos"), 1, glm::value_ptr( lightPosition ) );
            glUniform3fv( glGetUniformLocation(program, "viewPos"), 1, glm::value_ptr( context.GetCamera().Position() ) );
         });
      }

      // object 2 ( light source )
      {
         auto& program = addObject( shadersLight, obj, texture );

         program.LoadTransformation( [&lightPosition, c_lPos, &context](GLuint program)
         {
            glm::mat4 model = glm::mat4(1);
            model = glm::rotate(model, -(float)glfwGetTime() + glm::radians(0.0f), glm::vec3( 5.0, 80.0, 40.0 ));
            model = glm::translate( model, c_lPos );

            lightPosition = model * glm::vec4(c_lPos, 0.0);

            model = glm::scale(model, glm::vec3(0.2));

            glUniformMatrix4fv( glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model) );

            glm::mat4 view = glm::mat4(1);
            view = context.GetCamera().LookAt();
            glUniformMatrix4fv( glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view) );

            glm::mat4 projection = glm::mat4(1);
            projection = glm::perspective( glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f );
            glUniformMatrix4fv( glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection) );
         });
      }

      while ( !glfwWindowShouldClose(context.Window()) ) {
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         for ( auto& program : programs )
            program.Draw();

         glfwSwapBuffers(context.Window());
         glfwPollEvents();
      };
   }

   glfwTerminate();
   return 0;
}