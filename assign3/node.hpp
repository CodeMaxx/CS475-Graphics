#ifndef _NODE_HPP_
#define	_NODE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "model.hpp"
#include "gl_framework.hpp"


class node {
	GLuint vao,vbo;
	Model model;

	GLfloat tx,ty,tz,rx,ry,rz;
	glm::mat4 rotation;
	glm::mat4 translation;

	glm::mat3 normal_matrix;

	std::vector<node*> children;
	node* parent;

	void update_matrices();

	public:
		node (node*, Model);

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

#endif