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

GLfloat c_xpos = 1.5, c_ypos = 0.0, c_zpos = 5.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;

//! Global translation
int g_xtrans = 0, g_ytrans = 0, g_ztrans = -16000;
float trans_factor = 0.002;
int g_xtheta=0, g_ytheta=0, g_ztheta=0;
float rot_factor = 0.001;

double w_size = 7.0;

//Enable/Disable perspective view
bool enable_perspective=true, enable_playback = false;
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

node* ground;
node* dome;
node* slight;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack1;
std::vector<glm::mat4> matrixStack2;
std::vector<glm::mat4> matrixStack3;
std::vector<glm::mat4> matrixStack4;
std::vector<glm::mat4> matrixStack5;
int total_nodes=0;

node* curr_node;

int num_frames = 0;
double timer = 1.0/24;

int SCREEN_WIDTH=512;
int SCREEN_HEIGHT=512;
unsigned char *pRGB;

std::vector<std::vector<double>> keyframes;
std::vector<std::vector<double>> allframes;

void dumpFrame();
std::vector<std::vector<double>> interpolate_two_frames(int);
void interpolate_all_frames(void);
void read_keyframes();
void apply_frame(int kf_num);

#endif