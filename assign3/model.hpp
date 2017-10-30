#ifndef _MODEL_HPP_
#define	_MODEL_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


struct Model
{
  std::vector<float> pts;
  std::vector<float> color;
  std::vector<float> normal;
  std::vector<float> texture;
  int type; //0 ->cylinder 1->cuboid
  int num_vertex;
public:
  static Model draw_sphere(double radius, int Lats, int Longs);
  static Model draw_cylinder(double radius, double height, int Lats);
  static Model draw_frustum(double radius1, double radius2, double height, int Lats);
  static Model draw_cuboid(double xlength, double ylength, double zlength);
  Model()
  {
    num_vertex=0;
  }
};

#endif