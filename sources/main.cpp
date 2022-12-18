#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#if defined(_WIN64) || defined(_WIN32)
   #define GLUT_DISABLE_ATEXIT_HACK
   #define FREEGLUT_STATIC
   #include "GL/freeglut.h"
#endif

#include <iostream>
#include <fstream>
#include <streambuf>
#include <map>
#include <string>

#include "utils/filesystem/app_utils.hpp"

using namespace std;

GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

GLuint VBO;
GLuint VAO;
GLuint shaderProgram;

using Name = string;

struct Shader{
   GLuint shader;
   string file;
   const GLchar ** source;
};

std::map<Name,Shader> shaderPool;

const std::string readFile( const std::string& path )
{
   std::string result;
   std::ifstream t( path.c_str() );

   t.seekg(0, std::ios::end);   
   result.reserve(t.tellg());
   t.seekg(0, std::ios::beg);

   result.assign(( std::istreambuf_iterator<char>(t) ), std::istreambuf_iterator<char>() );
   return result;
}

Shader readShader( const std::string& path, GLenum type )
{
   Shader result;
   GLuint shader = glCreateShader(type);
   result.shader = shader;
   result.file = readFile( path );
   return result;
}

bool compileShader( Shader& shader )
{
   const GLchar* source = shader.file.c_str();
   glShaderSource(shader.shader, 1, &source, NULL);
   glCompileShader(shader.shader);

   GLint success;
   GLchar infoLog[512];
   glGetShaderiv(shader.shader, GL_COMPILE_STATUS, &success);

   if(!success)
   {
      glGetShaderInfoLog(shader.shader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
   }

   return success;
}

void loadShaders()
{
   std::string current_dir = utils::getCurrentDir();

   shaderPool["vertex"] = std::move(readShader( (current_dir + "/resources/shaders/vertex_shader").c_str(), GL_VERTEX_SHADER ));
   if ( !compileShader(shaderPool["vertex"]) ) return;

   shaderPool["fragment"] = readShader( (current_dir + "/resources/shaders/fragment_shader").c_str(), GL_FRAGMENT_SHADER );
   if ( !compileShader(shaderPool["fragment"]) ) return;

   shaderProgram = glCreateProgram();

   glAttachShader(shaderProgram, shaderPool["vertex"].shader);
   glAttachShader(shaderProgram, shaderPool["fragment"].shader);
   glLinkProgram(shaderProgram);
   glUseProgram(shaderProgram);

   glDeleteShader(shaderPool["vertex"].shader);
   glDeleteShader(shaderPool["fragment"].shader);
}

void init( )
{
   glGenBuffers(1, &VBO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);

   glGenVertexArrays(1, &VAO);
   glBindVertexArray(VAO);

   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   
   glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) 
{
   if(!glfwInit()){
      return -1;
   }

   // Create a GLFWwindow object that we can use for GLFW's functions
   GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
   glfwMakeContextCurrent(window);

   // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
   glewExperimental = GL_TRUE;
   // Initialize GLEW to setup the OpenGL Function pointers
   glewInit();

   // Define the viewport dimensions
   int width, height;
   glfwGetFramebufferSize(window, &width, &height);  
   glViewport(0, 0, width, height);

   loadShaders();
   init();

   while (!glfwWindowShouldClose(window))
   {
      // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
      glfwPollEvents();

      // Render
      // Clear the colorbuffer
      glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // Draw our first triangle
      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glBindVertexArray(0);

      // Swap the screen buffers
      glfwSwapBuffers(window);
   }

   return 0;
}