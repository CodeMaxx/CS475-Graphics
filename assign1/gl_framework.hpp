#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "glm/vec3.hpp"

#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

struct state
{
  char mode;
  std::vector<float> pts;
  std::vector<float> color;
  int xtheta, ytheta, ztheta;
  int xtrans, ytrans, ztrans;
  glm::vec3 centroid;
  int num_vertex;
  float zpos;
  //! Scale how much translation or rotation is required per key press
  float trans_factor;
  float rot_factor;

  state(): centroid(0.0f, 0.0f, 0.0f) {
    mode = 'I';
    xtheta = ytheta = ztheta = num_vertex = 0;
    zpos = 0;
    trans_factor = 0.01;
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
