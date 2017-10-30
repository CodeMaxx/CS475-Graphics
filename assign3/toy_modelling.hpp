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
GLuint vPosition,vColor, vNormal, texCoord, nodeNum;
GLuint uModelViewMatrix, viewMatrix, normalMatrix;


glm::mat4 global_rotation_matrix;
glm::mat4 global_translation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;


glm::mat4 model_matrix;
glm::mat4 view_matrix;

// Light switches
GLuint SWITCH1, SWITCH2, SWITCH3;
int switch1 = 1, switch2 = 1, switch3 = 1;

// Woody
std::vector<node*> woody;

//stretch
std::vector<node*> stretch;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack1;
std::vector<glm::mat4> matrixStack2;
int total_nodes=0;

node* curr_node;

#endif