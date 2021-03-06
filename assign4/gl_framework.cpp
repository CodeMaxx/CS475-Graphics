#include "gl_framework.hpp"
#include "node.hpp"
#include <fstream>
#include <sstream>
#include <cstdio>

extern GLfloat c_xrot,c_yrot,c_zrot;
extern bool enable_perspective;
extern bool enable_playback;
extern node *node1, *curr_node;
extern std::vector<node*> woody,stretch;
extern int switch1, switch2, switch3;
extern double w_size;
extern int g_xtrans, g_ytrans, g_ztrans, g_xtheta, g_ytheta, g_ztheta;
extern float  trans_factor,rot_factor;
extern void dumpFrame();
extern int num_frames;
extern std::vector<std::vector<double>> keyframes,allframes;
extern void read_keyframes();

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
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE){
      // Close window
      glfwSetWindowShouldClose(window, GL_TRUE);
    }


    if(mods % 2 != GLFW_MOD_SHIFT) {
      if(action == GLFW_PRESS) {
        switch(key) {
          // Light switches
          case GLFW_KEY_I: switch1 = !switch1;
                              break;
          case GLFW_KEY_O: switch2 = !switch2;
                              break;
          case GLFW_KEY_U: switch3 = !switch3;
                              break;
          case GLFW_KEY_P: enable_perspective = !enable_perspective;
                              break;
          case GLFW_KEY_Z: w_size = w_size > 0.5 ? w_size - 0.5 : w_size;
                              break;
          case GLFW_KEY_X: w_size = w_size < 10.5 ? w_size + 0.5 : w_size;
                              break;
          // Dump frame to file
          case GLFW_KEY_T: dumpFrame();
                            break;
          // Toggle between recording and playback mode
          case GLFW_KEY_R: enable_playback = !enable_playback;

                            if(enable_playback){
                              keyframes.clear();
                              allframes.clear();
                              read_keyframes();
                              glfwSetTime(0.0);
                              num_frames=0;
                            }
                              break;
          // Delete keyframe.txt
          case GLFW_KEY_Y: remove("keyframes.txt");
                              break;
        }
      }

      if(action == GLFW_PRESS) {
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

        // Character rotation
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

        // Character translation
        case GLFW_KEY_F: curr_node->dec_ty();
                            break;
        case GLFW_KEY_G: curr_node->inc_ty();
                            break;
        case GLFW_KEY_H: curr_node->dec_tx();
                            break;
        case GLFW_KEY_J: curr_node->inc_tx();
                            break;
        case GLFW_KEY_K: curr_node->dec_tz();
                            break;
        case GLFW_KEY_L: curr_node->inc_tz();
                            break;

        // Rotation about X, Y, Z respectively
        case GLFW_KEY_D:  g_ytheta -= 100;
                            break;
        case GLFW_KEY_A:  g_ytheta += 100;
                            break;
        case GLFW_KEY_W:  g_xtheta += 100;
                            break;
        case GLFW_KEY_S:  g_xtheta -= 100;
                            break;
        case GLFW_KEY_E:  g_ztheta -= 100;
                            break;
        case GLFW_KEY_Q:  g_ztheta += 100;
                            break;

        // Translation along positive Y, X, Z respectively
        case GLFW_KEY_C:  g_ytrans += 100;
                            break;
        case GLFW_KEY_V:  g_ytrans -= 100;
                            break;
        case GLFW_KEY_B:  g_xtrans += 100;
                            break;
        case GLFW_KEY_N:  g_xtrans -= 100;
                            break;
        case GLFW_KEY_M:  g_ztrans += 100;
                            break;
        case GLFW_KEY_COMMA:  g_ztrans -= 100;
                            break;
      }
    }
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
      case GLFW_KEY_Q: curr_node = stretch[0];
                        break;
      // stretch leg 1
      case GLFW_KEY_W: curr_node = stretch[1];
                        break;
      // stretch leg 2
      case GLFW_KEY_E: curr_node = stretch[2];
                        break;
      // stretch leg 3
      case GLFW_KEY_R: curr_node = stretch[3];
                        break;
      // stretch leg 4
      case GLFW_KEY_T: curr_node = stretch[4];
                        break;
      // stretch leg 5
      case GLFW_KEY_Y: curr_node = stretch[5];
                        break;
      // stretch leg 6
      case GLFW_KEY_U: curr_node = stretch[6];
                        break;
      // stretch leg 7
      case GLFW_KEY_I: curr_node = stretch[7];
                        break;
      // stretch leg 8
      case GLFW_KEY_O: curr_node = stretch[8];
                        break;
      }
    }
  }
};
