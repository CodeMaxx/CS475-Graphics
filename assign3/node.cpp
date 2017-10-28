#include "node.hpp"
#include <iostream>

extern std::vector<glm::mat4> matrixStack;
extern GLuint vPosition,vColor,transMatrix;

node::node(node* a_parent, Model m ){

	model = m;
	// initialize vao and vbo of the object;


	//Ask GL for a Vertex Attribute Objects (vao)
	glGenVertexArrays (1, &vao);
	//Ask GL for aVertex Buffer Object (vbo)
	glGenBuffers (1, &vbo);

	//bind them
	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);


	glBufferData (GL_ARRAY_BUFFER, m.pts.size() * sizeof (float) + m.color.size() * sizeof (float), NULL, GL_STATIC_DRAW);
    glBufferSubData( GL_ARRAY_BUFFER, 0, m.pts.size() * sizeof (float), &m.pts[0] );
    glBufferSubData( GL_ARRAY_BUFFER, m.pts.size() * sizeof (float),m.color.size() * sizeof (float), &m.color[0] );

	//setup the vertex array as per the shader
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	glEnableVertexAttribArray( vColor );
	glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m.pts.size()*sizeof(float)));


	// set parent

	if(a_parent == NULL){
		parent = NULL;
	}
	else{
		parent = a_parent;
		parent->add_child(this);
	}

	//initial parameters are set to 0;

	tx=ty=tz=rx=ry=rz=0;

	update_matrices();
}

void node::update_matrices(){

	rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
	rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
	rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

	translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));


}

void node::add_child(node* a_child){
	children.push_back(a_child);

}

void node::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
	tx = atx;
	ty = aty;
	tz = atz;
	rx = arx;
	ry = ary;
	rz = arz;

	update_matrices();
}

void node::render(){

	//matrixStack multiply
	glm::mat4* ms_mult = multiply_stack(matrixStack);

	glUniformMatrix4fv(transMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
	glBindVertexArray (vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, model.pts.size()/3);

	// for memory
	delete ms_mult;

}

void node::render_tree(){

	matrixStack.push_back(translation);
	matrixStack.push_back(rotation);

	render();
	for(int i=0;i<children.size();i++){
		children[i]->render_tree();
	}
	matrixStack.pop_back();
	matrixStack.pop_back();

}

void node::inc_rx(){
	rx++;
	update_matrices();
}


void node::inc_ry(){
	ry++;
	update_matrices();
}

void node::inc_rz(){
	rz++;
	update_matrices();
}

void node::dec_rx(){
	rx--;
	update_matrices();
}

void node::dec_ry(){
	ry--;
	update_matrices();
}

void node::dec_rz(){
	rz--;
	update_matrices();
}


glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
	glm::mat4* mult;
	mult = new glm::mat4(1.0f);

	for(int i=0;i<matStack.size();i++){
		*mult = (*mult) * matStack[i];
	}

	return mult;
}