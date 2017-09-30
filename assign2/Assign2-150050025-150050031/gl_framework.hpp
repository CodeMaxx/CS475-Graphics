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
  std::vector<float> axis_pts;
  std::vector<float> axis_color;

  // frustum variables
  float L,R,T,B,N,F;

  float Lw,Rw,Tw,Bw,Nw,Fw;
  glm::vec3 Ew, Cw, Uw;

  // frustum coordinates
  std::vector<float> frustum_pts;
  std::vector<float> frustum_color;
  glm::vec3 frustum_centroid;
  int frustum_vertex_num;

  //wcs variable
  glm::vec3 eye;
  glm::vec3 lookat_pt;
  glm::vec3 upvec;

  state()
  : frustum_centroid(0.0f, 0.0f, 0.0f){
    mode = 'I';
    g_xtheta = g_ytheta = g_ztheta = 0;
    g_xtrans = g_ytrans = g_ztrans = 0;
    g_scale = 10;
    trans_factor = 0.01;
    rot_factor = 0.1;
    scale_factor = 0.1;
    frustum_vertex_num = 0;
    Lw = -5.0;
    Rw = 5.0;
    Bw = -5.0;
    Tw = 5.0;
    Nw = -5000.0;
    Fw = 5000.0;
    Ew = glm::vec3(0.0,0.0,3.0);
    Cw = glm::vec3(0.0,0.0,0.0);
    Uw = glm::vec3(0.0,1.0,0.0);

  }

  glm::mat4 wcs_to_vcs(){
    glm::vec3 n = -(lookat_pt-eye)/glm::length(lookat_pt-eye);
    glm::vec3 u = glm::cross(upvec,n)/glm::length(glm::cross(upvec,n));
    glm::vec3 v = glm::cross(n,u);
    glm::vec3 e(-glm::dot(u,eye),-glm::dot(v,eye),-glm::dot(n,eye));
    glm::mat4 ret(u.x, v.x, n.x, 0,
                  u.y, v.y, n.y, 0,
                  u.z, v.z, n.z, 0,
                  e.x, e.y, e.z, 1);
    return ret;
  }

  glm::mat4 vcs_to_ccs() {
    glm::mat4 ret(2*N/(R+L), 0, 0, 0,
                  0, 2*N/(T+B), 0, 0,
                  (R-L)/(R+L), (T-B)/(T+B), -(F+N)/(F-N), -1,
                  0, 0, -2*F*N/(F-N), 0);
    return ret;
  }

  glm::mat4 view_matrix() {
    // std::cout<<Ew.z<<std::endl;
    return glm::ortho(Lw,Rw,Bw,Tw,Nw,Fw) * glm::lookAt(Ew, Cw, Uw) ;
  }

  glm::mat4 ndcs_to_dcs() {
    glm::mat4 ret((R+L)/2, 0, 0, 0,
                  0, (T+B)/2, 0, 0,
                  0, 0, 1/2, 0,
                  (R-L)/2, (T-B)/2, 1/2, 1);
    return ret;
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
