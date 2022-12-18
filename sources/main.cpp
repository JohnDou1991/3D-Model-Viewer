#include "common.h"

#include <iostream>

#include "config.h"
#include "DisplaySettings.h"

#include "utils/opengl/gl_utils.h"

void InitOpenGLContext()
{
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
   // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // this is for MacOS
}

GLFWwindow* InitOpenGLWindow()
{
   GLFWwindow* window = glfwCreateWindow(
       DisplaySettings::Window(DisplaySettings::Mode::HD).width()
     , DisplaySettings::Window(DisplaySettings::Mode::HD).height()
     , "LearnOpenGL"
     , NULL
     , NULL
   );

   if (!window)
   {
      std::cout << "Failed to create GLFW window..." << std::endl;
      glfwTerminate();
      return nullptr;
   }
   glfwMakeContextCurrent(window);
   return window;
}

bool IsGLADOk()
{
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      std::cout << "Failed to initialize GLAD..." << std::endl;
      return false;
   }
   return true;
}

void frameBufferSizeCallback(GLFWwindow*, int width, int height)
{
   glViewport( 0, 0, width, height );
}

void keyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
   switch(key)
   {
      case GLFW_KEY_ESCAPE:
      {
         glfwSetWindowShouldClose(window,1);
         break;
      }
      default:
         if ( DEBUG_KEYBOARD )
            std::cout << "key: " << key << " scancode: " << scancode << " action: " << action << " mods: " << mods << std::endl;
         break;
   }
}

GLuint VBO;
GLuint VAO;

float vertices[] = {
  -0.5f, -0.5f, 0.0f,
   0.5f, -0.5f, 0.0f,
   0.0f,  0.5f, 0.0f
};

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv)
{
   InitOpenGLContext();

   auto* window = InitOpenGLWindow();
   if(!window)
      return -1;

   if(!IsGLADOk())
      return -1;

   frameBufferSizeCallback(nullptr, DisplaySettings::Window(DisplaySettings::Mode::HD).width(), DisplaySettings::Window(DisplaySettings::Mode::HD).height() );
   glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
   glfwSetKeyCallback(window,keyPressedCallback);

   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

   GLuint shaderProgram = utils::loadShaders();

   glGenBuffers(1,&VBO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);

   glGenVertexArrays(1, &VAO);
   glBindVertexArray(VAO);

   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

   glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);

   while ( !glfwWindowShouldClose(window) )
   {
      glClear(GL_COLOR_BUFFER_BIT);

      // Draw our first triangle
      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      glBindVertexArray(0);

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glfwTerminate();
   return 0;
}