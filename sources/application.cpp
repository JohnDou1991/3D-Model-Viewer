#include "application.hpp"

#include "common.h"

#include "utils/filesystem/app_utils.hpp"

#include "core/ICamera.hpp"
#include "core/IScene.hpp"
#include "core/IShaderManager.hpp"
#include "core/ITextureManager.hpp"
#include "core/context/IContext.hpp"
#include "core/context/IWindow.hpp"
#include "utils/opengl/definitions.h"
#include "utils/opengl/program.h"

#include "gtc/type_ptr.hpp"

#include "utils/image_loader.h"

#include "objects/object.hpp"

#include "utils/vertices/color.h"
#include "utils/vertices/normal.h"
#include "utils/vertices/position.h"
#include "utils/vertices/texture.h"

#include "utils/vertices.h"

#include "objects/light/directional.hpp"
#include "objects/light/point.hpp"
#include "objects/light/spot.hpp"

#include "objects/model.hpp"

#include "stb_image.h"

#include "assets/cube.hpp"

struct LightSource {
   LightSource( glm::vec3 position ) 
      : current_position(position)
      , origin_position(position)
   {

   }
   glm::vec3 current_position;
   const glm::vec3 origin_position;
};

Application::Application()
    : m_context( core::CreateContext() )
    , m_camera( core::CreateCamera(*m_context) )
    , m_scene( core::CreateScene() )
    , m_shaderManager( core::CreateShaderManager() )
    , m_textureManager( core::CreateTextureManager() )
{

}

Application::~Application()
{

}

void Application::Init()
{
   stbi_set_flip_vertically_on_load(true);
   m_scene->AddObject( std::make_unique<assets::Cube>(m_shaderManager, m_textureManager) );
}

void Application::LoadObjects()
{
   object::Object obj( std::make_unique<vertice::Position>( vertices::cube1, 3 )
                     , std::make_unique<vertice::Normal>( vertices::cube1_normals, 3 )
                     , std::make_unique<vertice::Texture>( vertices::cube1_tex_coords, 2 )
   );

   Textures textures;
   textures.emplace_back( utils::ImageLoader().Load( utils::getCurrentDir() + "/resources/textures/container2.png" ) );
   textures.emplace_back( utils::ImageLoader().Load( utils::getCurrentDir() + "/resources/textures/container2_specular.png" ) );

   m_models.emplace_back(std::move(obj), std::move(textures));
}

void Application::LoadLightSources()
{
   const object::light::Light::Color color{
      glm::vec3(0.1, 0.1, 0.1), // ambient
      glm::vec3(0.5, 0.5, 0.5), // diffuse
      glm::vec3(1.0, 1.0, 1.0)  // specular
   };
   // const object::light::Light::Attenuation attenuation{ 1.0f, 0.09f, 0.032f };
   // const object::light::Light::Attenuation attenuation{ 1.0f, 0.35f, 0.44f };
   const object::light::Light::Attenuation attenuation{ 1.0f, 0.7f, 1.8f };

   m_sources.emplace_back( glm::vec3(1,1,1) );
   // m_sources.emplace_back( glm::vec3(1,2,1) );
   // m_sources.emplace_back( glm::vec3(1,3,1) );
   // m_sources.emplace_back( glm::vec3(1,4,1) );

   m_lights.emplace_back( new object::light::Directional(color, attenuation, glm::vec3(3)) );
   m_lights.emplace_back( new object::light::Spot(color, attenuation, m_camera->Position(), m_camera->Front(), 12.5f, 17.5f) );

   for ( auto& source : m_sources )
      m_lights.emplace_back( new object::light::Point(color, attenuation, source.current_position) );
}

void Application::LoadScene()
{
   LoadShaders();
   LoadObjects();
   LoadLightSources();
}

void Application::LoadShaders()
{
   m_shaders.object[ShaderType::VERTEX].push_back("light.vs");
   m_shaders.object[ShaderType::FRAGMENT].push_back("lightObject.fs");
   m_shaders.light[ShaderType::VERTEX].push_back("light.vs");
   m_shaders.light[ShaderType::FRAGMENT].push_back("lightSource.fs");
}

void Application::Start()
{
   // scene s1;
   // s1.addObject(model, ...);
   // s1.addLight(model, ...);
   // s1.addTerrain(geometry, ...);
   // s1.addCamera(...);
   // s1.draw();
   // object::Model m1( utils::getCurrentDir() + "/resources/models/backpack.obj" );

   {
      std::vector<utils::opengl::Program> programs;
      programs.reserve(32);

      auto addObject = [this, &programs]( 
         const Shaders& shaders
       , const object::Object& obj
       , const Textures& textures ) -> utils::opengl::Program&
      {
         programs.emplace_back();
         utils::opengl::Program& program = programs.back();

         program.LoadShaders( shaders );
         program.LoadObject( obj );

         for ( auto& texture : textures )
            program.LoadTexture( texture );

         return program;
      };

      auto sceneTransformation = [this](GLuint program)
      {
         // camera position
         glm::mat4 view = glm::mat4(1);
         view = m_camera->LookAt();
         glUniformMatrix4fv( glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view) );

         // projection
         glm::mat4 projection = glm::mat4(1);
         projection = glm::perspective( glm::radians(m_context->FieldOfView()), m_context->GetWindow().AspectRatio(), 0.1f, 100.0f );
         glUniformMatrix4fv( glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projection) );

         for ( auto& light : m_lights )
            light->Process(program);

         glUniform3fv( glGetUniformLocation(program, "viewPos"), 1, glm::value_ptr( m_camera->Position() ) );
      };

      // { // object 1
      //    programs.emplace_back();
      //    auto& program = programs.back();

      //    program.LoadShaders( m_shaders.object );
      //    program.LoadModel( utils::getCurrentDir() + "/resources/models/backpack.obj" );
      //    program.LoadTransformation( [this,&sceneTransformation](GLuint program)
      //    {
      //       glm::mat4 model = glm::mat4(1);
      //       model = glm::rotate(model, (float)m_context->GetTime()/2 + glm::radians(45.0f), glm::vec3( 0.0, 20.0, 0.0 ));
      //       model = glm::translate( model, glm::vec3(0,0,0) );
      //       glUniformMatrix4fv( glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model) );

      //       glUniform3fv( glGetUniformLocation(program, "material.color.ambient"), 1, glm::value_ptr( glm::vec3( 1.0, 0.5, 0.31 )) );
      //       glUniform3fv( glGetUniformLocation(program, "material.color.diffuse"), 1, glm::value_ptr( glm::vec3( 1.0, 0.5, 0.31 )) );
      //       glUniform3fv( glGetUniformLocation(program, "material.color.specular"), 1, glm::value_ptr( glm::vec3( 0.5, 0.5, 0.5 )) );

      //       glUniform1f( glGetUniformLocation(program, "material.shininess"), 64.0 );

      //       sceneTransformation(program);
      //    });
      // }

      for ( auto& model : m_models)
      { // object 2
         auto& program = addObject( m_shaders.object, model.first, model.second );
         glm::vec3 position(0,0,0);
         program.LoadTransformation([this, &sceneTransformation, position](GLuint program)
         {
            glm::mat4 model = glm::mat4(1);
            // model = glm::rotate(model, (float)glfwGetTime()/2 + glm::radians(45.0f), glm::vec3( 0.0, 0.0, 20.0 ));
            model = glm::translate( model, position );
            glUniformMatrix4fv( glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model) );

            glUniform3fv( glGetUniformLocation(program, "material.color.ambient"), 1, glm::value_ptr( glm::vec3( 1.0, 0.6, 0.51 )) );
            glUniform3fv( glGetUniformLocation(program, "material.color.diffuse"), 1, glm::value_ptr( glm::vec3( 1.0, 0.6, 0.51 )) );
            glUniform3fv( glGetUniformLocation(program, "material.color.specular"), 1, glm::value_ptr( glm::vec3( 0.9, 0.9, 0.9 )) );

            glUniform1f( glGetUniformLocation(program, "material.shininess"), 256.0 );

            sceneTransformation(program);
         });
      }

      // {
      //    for ( int i = 0; i < 1; ++i ) 
      //    {
      //       auto& program = addObject( m_shaders.object, obj, textures );

      //       glm::vec3 position( (rand() - RAND_MAX/2) % 4, (rand() - RAND_MAX/2) % 4, (rand() - RAND_MAX/2) % 4 );
      //       // glm::vec3 position(0,0,0);
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

      { // object 3 ( light source )
         for ( auto& source : m_sources )
         {
            auto& program = addObject( m_shaders.light, m_models.front().first, {} );

            program.LoadTransformation( [this, &source, &sceneTransformation](GLuint program)
            {
               glm::mat4 model = glm::mat4(1);
               model = glm::rotate(model, -(float)m_context->GetTime()/2 + glm::radians(0.0f), glm::vec3( 0.0, 20.0, 0.0 ));
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

      while ( !m_context->GetWindow().ShouldClose() ) {
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         // programs.front().Draw2();
         for ( int i = 0; i < programs.size(); ++i )
            programs[i].Draw();

         m_scene->Draw();

         m_context->GetWindow().SwapBuffers();
         m_context->PollEvents();
      };
   }
}