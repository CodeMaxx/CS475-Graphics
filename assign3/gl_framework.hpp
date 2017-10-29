#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "node.hpp"

#define BUFFER_OFFSET( offset )  ((GLvoid*) (offset))

struct state
{
  int g_xtheta, g_ytheta, g_ztheta; //number of clicks
  int g_xtrans, g_ytrans, g_ztrans;
  float trans_factor;
  float rot_factor;

  //for drawing x,y,z axis
  std::vector<float> axis_pts;
  std::vector<float> axis_color;

  state() {
    g_xtheta = g_ytheta = g_ztheta = 0;
    g_xtrans = g_ytrans = g_ztrans = 0;
    trans_factor = 0.05;
    rot_factor = 0.1;
  }
};

namespace cse
{
  //! Initialize GL State
  void initGL(void);

  //!GLFW Error Callback
  void error_callback(int error, const char* description);
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
  //!GLFW mouse callback
  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
};

#endif
