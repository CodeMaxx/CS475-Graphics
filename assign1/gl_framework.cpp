#include "gl_framework.hpp"

namespace cse
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
    //Enable Gourard shading
    glShadeModel(GL_SMOOTH);
  }

  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }

  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }

  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    state *s;
    s = (state*)glfwGetWindowUserPointer(window);
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if(key == GLFW_KEY_M && action == GLFW_PRESS){
      s->mode = 'M';
      std::cout << "Modelling Mode" << std::endl;
    }
    else if(key == GLFW_KEY_I && action == GLFW_PRESS){
      s->mode = 'I';
      std::cout << "Inspection Mode" << std::endl;
    }
  }

  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {
      if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
      {
         double xpos, ypos;
         //getting cursor position
         glfwGetCursorPos(window, &xpos, &ypos);
         state* st = (state*) glfwGetWindowUserPointer(window);
         st->xpos = xpos;
         st->ypos = ypos;
         st->new_point = 1;
         std::cout << "DEBUG: " << xpos << " " << ypos << std::endl;
      }
  }
};



