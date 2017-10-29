#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "node.hpp"

#define BUFFER_OFFSET( offset )  ((GLvoid*) (offset))

struct state
{
  char mode;
  int g_xtheta, g_ytheta, g_ztheta; //number of clicks
  int g_xtrans, g_ytrans, g_ztrans;
  float trans_factor;
  float rot_factor;

  //for drawing x,y,z axis
  std::vector<float> axis_pts;
  std::vector<float> axis_color;

  // frustum variables
  float L,R,T,B,N,F;

  // frustum coordinates
  std::vector<float> frustum_pts;
  std::vector<float> frustum_color;
  int frustum_vertex_num;

  //wcs variable
  glm::vec3 eye;
  glm::vec3 lookat_pt;
  glm::vec3 upvec;

  // our frustum variable (window)
  float Lw,Rw,Tw,Bw,Nw,Fw;
  glm::vec3 Ew, Cw, Uw;

  state() {
    mode = 'I';
    g_xtheta = g_ytheta = g_ztheta = 0;
    g_xtrans = g_ytrans = g_ztrans = 0;
    trans_factor = 0.05;
    rot_factor = 0.1;
    frustum_vertex_num = 0;
    Lw = -2.0;
    Rw = 2.0;
    Bw = -2.0;
    Tw = 2.0;
    Nw = -5000.0;
    Fw = 5000.0;
    Ew = glm::vec3(0.0,0.0,3.0);
    Cw = glm::vec3(0.0,0.0,0.0);
    Uw = glm::vec3(0.0,1.0,0.0);

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
