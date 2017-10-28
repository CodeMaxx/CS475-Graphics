#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "gl_framework.hpp"

class node {
	GLuint vao,vbo;
	GLuint num_vertices;

	std::size_t vertex_buffer_size;
	std::size_t color_buffer_size;

	GLfloat tx,ty,tz,rx,ry,rz;
	glm::mat4 rotation;
	glm::mat4 translation;

	std::vector<node*> children;
	node* parent;

	void update_matrices();

	public:
		node (node*, GLuint, glm::vec3*,  glm::vec3*, std::size_t, std::size_t);

		void add_child(node*);
		void render();
		void change_parameters(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
		void render_tree();
		void inc_rx();
		void inc_ry();
		void inc_rz();
		void dec_rx();
		void dec_ry();
		void dec_rz();
};

glm::mat4* multiply_stack(std::vector <glm::mat4> );