#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "glm/vec3.hpp"

struct state
{
  char mode;
  std::vector<float> pts;
  int xtheta, ytheta, ztheta;
  int xtrans, ytrans, ztrans;
  glm::vec3 centroid;

  state(): centroid(0.0f, 0.0f, 0.0f) {
    mode = 'I';
    xtheta = ytheta = ztheta = 0;
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
