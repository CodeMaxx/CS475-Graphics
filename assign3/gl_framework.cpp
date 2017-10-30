#include "gl_framework.hpp"
#include "node.hpp"
#include <fstream>
#include <sstream>

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;
extern node *node1, *curr_node;
extern std::vector<node*> woody,stretch;

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
    if (key == GLFW_KEY_ESCAPE){
      // Close window
      glfwSetWindowShouldClose(window, GL_TRUE);
    }

    switch(key) {
      // Woody hip
      case GLFW_KEY_0: curr_node = woody[0];
                        break;
      // Woody left top leg
      case GLFW_KEY_1: curr_node = woody[1];
                        break;
      // Woody right top leg
      case GLFW_KEY_2: curr_node = woody[2];
                        break;
      // Woody left bottom leg
      case GLFW_KEY_3: curr_node = woody[3];
                        break;
      // Woody right bottom leg
      case GLFW_KEY_4: curr_node = woody[4];
                        break;
      // Woody torso
      case GLFW_KEY_5: curr_node = woody[5];
                        break;
      // Woody neck
      case GLFW_KEY_6: curr_node = woody[7];
                        break;
      // Woody head
      case GLFW_KEY_7: curr_node = woody[8];
                        break;
      // Woody left arm top
      case GLFW_KEY_8: curr_node = woody[11];
                        break;
      // Woody right arm top
      case GLFW_KEY_9: curr_node = woody[12];
                        break;
      case GLFW_KEY_LEFT: curr_node->dec_ry();
                          break;
      case GLFW_KEY_RIGHT: curr_node->inc_ry();
                          break;
      case GLFW_KEY_UP: curr_node->dec_rx();
                          break;
      case GLFW_KEY_DOWN: curr_node->inc_rx();
                          break;
      case GLFW_KEY_PAGE_UP: curr_node->dec_rz();
                          break;
      case GLFW_KEY_PAGE_DOWN: curr_node->inc_rz();
                          break;
      case GLFW_KEY_P: enable_perspective = !enable_perspective;
                          break;
      case GLFW_KEY_A: c_yrot -= 1.0;
                          break;
      case GLFW_KEY_D: c_yrot += 1.0;
                          break;
      case GLFW_KEY_W: c_xrot -= 1.0;
                          break;
      case GLFW_KEY_S: c_xrot += 1.0;
                          break;
      case GLFW_KEY_Q: c_zrot -= 1.0;
                          break;
      case GLFW_KEY_E: c_zrot += 1.0;
                          break;

      // Translation along positive Y, X, Z respectively
      case GLFW_KEY_KP_2:  st->g_ytrans ++;
                          break;
      case GLFW_KEY_KP_5:  st->g_ytrans --;
                          break;
      case GLFW_KEY_KP_1:  st->g_xtrans ++;
                          break;
      case GLFW_KEY_KP_3:  st->g_xtrans --;
                          break;
      case GLFW_KEY_KP_4:  st->g_ztrans ++;
                          break;
      case GLFW_KEY_KP_6:  st->g_ztrans --;
                          break;

      // DEFAULT CASE
      default: std::cout << "Key not recognised in this mode." << std::endl;
    }

    if(mods % 2 == GLFW_MOD_SHIFT) {
      switch(key) {
        // Woody left arm bottom
      case GLFW_KEY_0: curr_node = woody[13];
                        break;
      // Woody right arm bottom
      case GLFW_KEY_1: curr_node = woody[14];
                        break;
      // Woody left palm
      case GLFW_KEY_2: curr_node = woody[15];
                        break;
      // Woody right palm
      case GLFW_KEY_3: curr_node = woody[16];
                        break;
      // Woody lef foot
      case GLFW_KEY_4: curr_node = woody[17];
                        break;
      // Woody right foot
      case GLFW_KEY_5: curr_node = woody[18];
                        break;
      // stretch base
      case GLFW_KEY_6: curr_node = stretch[0];
                        break;
      // stretch leg 1
      case GLFW_KEY_7: curr_node = stretch[1];
                        break;
      // // Woody left top leg
      // case GLFW_KEY_8: curr_node = woody[18];
      //                   break;
      // DEFAULT CASE
      default: std::cout << "Key not recognised in this mode." << std::endl;
      }
    }
  }
};
