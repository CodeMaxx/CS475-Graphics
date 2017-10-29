#ifndef _TOY_HPP_
#define _TOY_HPP_

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "node.hpp"
#include "model.hpp"

//! The pointer to the GLFW window
GLFWwindow* window;
GLuint shaderProgram;

//! State variable passed to GLFW
state st;

GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 2.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

//! Global translation
int g_xtrans = 0, g_ytrans = 0, g_ztrans = 0;
float trans_factor = 0.05;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=false;
//Shader program attribs
GLuint vPosition,vColor;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

node* root_node;
node* curr_node;
node* node1;
node* node2;
node* node3;

#endif