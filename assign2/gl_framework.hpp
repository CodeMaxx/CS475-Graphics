#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "glm/vec3.hpp"

#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

struct Model
{
  std::vector<float> pts;
  std::vector<float> color;
  float xtheta, ytheta, ztheta;
  float xtrans, ytrans, ztrans; 
  float xscale, yscale, zscale;
  glm::vec3 centroid;
  int num_vertex;
  Model(): centroid(0.0f, 0.0f, 0.0f) {
    num_vertex = 0;
  }
};

struct state
{
  char mode;
  int g_xtheta, g_ytheta, g_ztheta; //number of clicks
  int g_xtrans, g_ytrans, g_ztrans;
  int g_scale;
  // float zpos;
  //! Scale how much translation or rotation is required per key press
  float trans_factor;
  float rot_factor;
  float scale_factor;
  Model model[3]; 

  //frustum variables
  float L,R,T,B,N,F;

  //wcs variable
  glm::vec3 eye;
  glm::vec3 lookat_pt;
  glm::vec3 upvec;

  state(){
    mode = 'I';
    g_xtheta = g_ytheta = g_ztheta = 0;
    g_xtrans = g_ytrans = g_ztrans = 0;
    g_scale = 10;
    trans_factor = 0.01;
    rot_factor = 0.1;
    scale_factor = 0.1;
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
