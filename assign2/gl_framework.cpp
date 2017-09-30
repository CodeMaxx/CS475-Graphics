#include "gl_framework.hpp"
#include <fstream>
#include <sstream>

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
    state *st;
    st = (state*)glfwGetWindowUserPointer(window);
    //!Close the window if the ESC key was pressed
    if(action == GLFW_PRESS) {
      if (key == GLFW_KEY_ESCAPE){
        // Close window
        glfwSetWindowShouldClose(window, GL_TRUE);
      }
        switch(key) {
          // Translation along positive Y, X, Z respectively
          case GLFW_KEY_W:  st->g_ytrans ++;
                            break;
          case GLFW_KEY_S:  st->g_ytrans --;
                            break;
          case GLFW_KEY_A:  st->g_xtrans ++;
                            break;
          case GLFW_KEY_D:  st->g_xtrans --;
                            break;
          case GLFW_KEY_Z:  st->g_ztrans ++;
                            break;
          case GLFW_KEY_X:  st->g_ztrans --;
                            break;
          // Rotation about X, Y, Z respectively
          case GLFW_KEY_UP: st->g_xtheta ++;
                            break;
          case GLFW_KEY_DOWN: st->g_xtheta --;
                            break;
          case GLFW_KEY_LEFT: st->g_ytheta ++;
                            break;
          case GLFW_KEY_RIGHT: st->g_ytheta --;
                            break;
          case GLFW_KEY_PAGE_UP: st->g_ztheta ++;
                            break;
          case GLFW_KEY_PAGE_DOWN: st->g_ztheta --;
                            break;
          case GLFW_KEY_1:  // WCS to VCS
                            st->mode='1';
                            break;
          case GLFW_KEY_2:  // VCS to CCS
                            st->mode='2';
                            break;
          case GLFW_KEY_3:  // CCS to NDCS
                            st->mode='3';
                            break;
          case GLFW_KEY_4:  // NDCS to DCS
                            st->mode='4';
                            break;

          // case GLFW_KEY_R: st->xtrans = -st->centroid.x/st->trans_factor;
          //                   st->ytrans = -st->centroid.y/st->trans_factor;
          //                   st->ztrans = -st->centroid.z/st->trans_factor;
          //                   break;
          // Default case
          default: std::cout << "Key not recognised in this mode." << std::endl;
        }
    }
  }
};
