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

#include "objects/light/directional.hpp"
#include "objects/light/point.hpp"
#include "objects/light/spot.hpp"

#include "objects/model.hpp"

#include "stb_image.h"

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
   utils::opengl::Context context;

   stbi_set_flip_vertically_on_load(true);

   ShaderList shadersObject;
   shadersObject[ShaderType::VERTEX].push_back("light.vs");
   shadersObject[ShaderType::FRAGMENT].push_back("lightObject.fs");

   ShaderList shadersLight;
   shadersLight[ShaderType::VERTEX].push_back("light.vs");
   shadersLight[ShaderType::FRAGMENT].push_back("lightSource.fs");

   // object::Model m1( utils::getCurrentDir() + "/resources/models/backpack.obj" );

   vertice::Object obj;
   obj.Add( new vertice::Position( vertices::cube1, 3 ));
   // obj.Add( new vertice::Normal( vertices::cube1_normals, 3 ));
   // obj.Add( new vertice::Texture( vertices::cube1_tex_coords, 2 ));

   using Textures = std::vector<utils::Image>;

   // Textures textures;
   // textures.emplace_back( utils::ImageLoader().Load( utils::getCurrentDir() + "/resources/textures/container2.png" ) );
   // textures.emplace_back( utils::ImageLoader().Load( utils::getCurrentDir() + "/resources/textures/container2_specular.png" ) );

   using LightSources = std::vector<std::unique_ptr<object::light::Light>>;
   
   const object::light::Light::Color color{
      glm::vec3(0.1, 0.1, 0.1), // ambient
      glm::vec3(0.5, 0.5, 0.5), // diffuse
      glm::vec3(1.0, 1.0, 1.0)  // specular
   };
   // const object::light::Light::Attenuation attenuation{ 1.0f, 0.09f, 0.032f };
   // const object::light::Light::Attenuation attenuation{ 1.0f, 0.35f, 0.44f };
   const object::light::Light::Attenuation attenuation{ 1.0f, 0.7f, 1.8f };

   struct LightSource {
      LightSource( glm::vec3 position ) 
         : current_position(position)
         , origin_position(position)
      {

      }
      glm::vec3 current_position;
      const glm::vec3 origin_position;
   };

   std::vector<LightSource> sources;
   // sources.emplace_back( glm::vec3(1,1,1) );
   sources.emplace_back( glm::vec3(1,2,1) );
   // sources.emplace_back( glm::vec3(1,3,1) );
   // sources.emplace_back( glm::vec3(1,4,1) );

   LightSources lights;
   lights.emplace_back( new object::light::Directional(color, attenuation, glm::vec3(3)) );
   lights.emplace_back( new object::light::Spot(color, attenuation, context.GetCamera().Position(), context.GetCamera().Front(), 12.5f, 17.5f) );

   for ( auto& source : sources )
      lights.emplace_back( new object::light::Point(color, attenuation, source.current_position) );

   {
      std::vector<utils::opengl::Program> programs;
      programs.reserve(32);

      auto addObject = [&programs, &context]( 
         const ShaderList& shaders
       , const vertice::Object& obj
       , const Textures& textures ) -> utils::opengl::Program&
      {
         programs.emplace_back(context);
         utils::opengl::Program& program = programs.back();

         program.LoadShaders( shaders );
         program.LoadObject( obj );

         for ( auto& texture : textures )
            program.LoadTexture( texture );

         return program;
      };

      auto sceneTransformation = [&lights, &context](GLuint program)
      {
         // camera position
         glm::mat4 view = glm::mat4(1);
         view = context.GetCamera().LookAt();
         glUniformMatrix4fv( glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view) );

         // projection
         glm::mat4 projection = glm::mat4(1);
         projection = glm::perspective( glm::radians(context.FieldOfView()), context.AspectRatio(), 0.1f, 100.0f );
         glUniformMatrix4fv( glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection) );

         for ( auto& light : lights )
            light->Process(program);

         glUniform3fv( glGetUniformLocation(program, "viewPos"), 1, glm::value_ptr( context.GetCamera().Position() ) );
      };

      // object 1
      programs.emplace_back(context);
      auto& program = programs.back();

      program.LoadShaders( shadersObject );
      program.LoadModel( utils::getCurrentDir() + "/resources/models/backpack.obj" );
      program.LoadTransformation( [&sceneTransformation](GLuint program)
      {
         glm::mat4 model = glm::mat4(1);
         model = glm::rotate(model, (float)glfwGetTime()/2 + glm::radians(45.0f), glm::vec3( 0.0, 20.0, 0.0 ));
         model = glm::translate( model, glm::vec3(0,0,0) );
         glUniformMatrix4fv( glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model) );

         glUniform3fv( glGetUniformLocation(program, "material.color.ambient"), 1, glm::value_ptr( glm::vec3( 1.0, 0.5, 0.31 )) );
         glUniform3fv( glGetUniformLocation(program, "material.color.diffuse"), 1, glm::value_ptr( glm::vec3( 1.0, 0.5, 0.31 )) );
         glUniform3fv( glGetUniformLocation(program, "material.color.specular"), 1, glm::value_ptr( glm::vec3( 0.5, 0.5, 0.5 )) );

         glUniform1f( glGetUniformLocation(program, "material.shininess"), 64.0 );

         sceneTransformation(program);
      });

      // {
      //    for ( int i = 0; i < 10; ++i ) 
      //    {
      //       auto& program = addObject( shadersObject, obj, textures );

      //       glm::vec3 position( (rand() - RAND_MAX/2) % 4, (rand() - RAND_MAX/2) % 4, (rand() - RAND_MAX/2) % 4 );

      //       program.LoadTransformation( [&sceneTransformation, position](GLuint program)
      //       {
      //          glm::mat4 model = glm::mat4(1);
      //          // model = glm::rotate(model, (float)glfwGetTime()/2 + glm::radians(45.0f), glm::vec3( 0.0, 0.0, 20.0 ));
      //          model = glm::translate( model, position );
      //          glUniformMatrix4fv( glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model) );

      //          glUniform3fv( glGetUniformLocation(program, "material.color.ambient"), 1, glm::value_ptr( glm::vec3( 1.0, 0.5, 0.31 )) );
      //          glUniform3fv( glGetUniformLocation(program, "material.color.diffuse"), 1, glm::value_ptr( glm::vec3( 1.0, 0.5, 0.31 )) );
      //          glUniform3fv( glGetUniformLocation(program, "material.color.specular"), 1, glm::value_ptr( glm::vec3( 0.5, 0.5, 0.5 )) );

      //          glUniform1f( glGetUniformLocation(program, "material.shininess"), 64.0 );

      //          sceneTransformation(program);
      //       });
      //    }
      // }

      // object 2 ( light source )
      {
         for ( auto& source : sources )
         {
            auto& program = addObject( shadersLight, obj, {} );

            program.LoadTransformation( [&source, &sceneTransformation, &context](GLuint program)
            {
               glm::mat4 model = glm::mat4(1);
               model = glm::rotate(model, -(float)glfwGetTime()/2 + glm::radians(0.0f), glm::vec3( 0.0, 20.0, 0.0 ));
               glm::vec3 pos = source.origin_position;
               // model = glm::translate( model, pos += sin(glfwGetTime()) );
               model = glm::translate( model, pos = glm::vec3(2.0, 0.0, 0.0) );

               source.current_position = model * glm::vec4(pos, 0.0);

               model = glm::scale(model, glm::vec3(0.2));

               glUniformMatrix4fv( glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model) );

               sceneTransformation(program);
            });
         }
      }

      while ( !glfwWindowShouldClose(context.Window()) ) {
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         programs.front().Draw2();
         for ( int i = 1; i < programs.size(); ++i )
            programs[i].Draw();

         glfwSwapBuffers(context.Window());
         glfwPollEvents();
      };
   }

   glfwTerminate();
   return 0;
}