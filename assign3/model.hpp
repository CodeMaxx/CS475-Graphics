#ifndef _MODEL_HPP_
#define	_MODEL_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "gl_framework.hpp"


struct Model
{
  std::vector<float> pts;
  std::vector<float> color;
  std::vector<float> normal;
  int num_vertex;
public:
  static Model draw_sphere(double radius, int Lats, int Longs);
  Model()
  {
    num_vertex=0;
  }
};

#endif