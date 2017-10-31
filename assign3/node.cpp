#include "node.hpp"

extern GLuint vPosition, vColor, vNormal, texCoord, uModelViewMatrix, normalMatrix, nodeNum;
extern int total_nodes;

node::node(node* a_parent, Model m, GLuint texture ){

	model = m;
	node_number =total_nodes;
	total_nodes++;
	tex=texture;
	// std::cout<<"node texture"<<tex<<" "<<node_number<<std::endl;
	// initialize vao and vbo of the object;


	//Ask GL for a Vertex Attribute Objects (vao)
	glGenVertexArrays (1, &vao);
	//Ask GL for aVertex Buffer Object (vbo)
	glGenBuffers (1, &vbo);

	//bind them
	glBindVertexArray (vao);
	glBindBuffer (GL_ARRAY_BUFFER, vbo);

	glBufferData (GL_ARRAY_BUFFER, m.pts.size() * sizeof (float) + m.texture.size() * sizeof (float) + m.normal.size() * sizeof(float), NULL, GL_STATIC_DRAW);
	glBufferSubData( GL_ARRAY_BUFFER, 0, m.pts.size() * sizeof (float), &m.pts[0] );
	glBufferSubData( GL_ARRAY_BUFFER, m.pts.size() * sizeof (float), m.texture.size() * sizeof (float), &m.texture[0] );
	glBufferSubData( GL_ARRAY_BUFFER, m.pts.size() * sizeof (float) + m.texture.size() * sizeof (float), m.normal.size() * sizeof(float), &m.normal[0] );

	//setup the vertex array as per the shader
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	glEnableVertexAttribArray( texCoord );
	glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m.pts.size()*sizeof(float)));

	glEnableVertexAttribArray( vNormal );
  	glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m.pts.size()*sizeof(float) + m.texture.size()*sizeof(float)) );


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

void node::render(std::vector<glm::mat4>* matrixStack){

	//matrixStack multiply
	glm::mat4* ms_mult = multiply_stack(*matrixStack);

	glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
	normal_matrix = glm::transpose (glm::inverse(glm::mat3(*ms_mult)));
	glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
	glBindVertexArray (vao);

	if(model.type==1)
	{
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, model.pts.size()/4);
	}
	else if(model.type==2)
	{
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, 0, model.pts.size()/4/4);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, model.pts.size()/4/4, model.pts.size()/4/2);
		glBindTexture(GL_TEXTURE_2D, tex);
		glDrawArrays(GL_TRIANGLES, model.pts.size()*3/4/4, model.pts.size()/4/4);
	}
	else if(model.type==3)
	{
		for(int i=0;i<6;i++){
			glBindTexture(GL_TEXTURE_2D, tex);
			glDrawArrays(GL_TRIANGLES, i*model.pts.size()/6/4, model.pts.size()/6/4);
		}

	}


	// for memory
	delete ms_mult;

}

void node::render_tree(std::vector<glm::mat4>* matrixStack){

	matrixStack->push_back(translation);
	matrixStack->push_back(rotation);

	render(matrixStack);
	for(int i=0;i<children.size();i++){
		children[i]->render_tree(matrixStack);
	}
	matrixStack->pop_back();
	matrixStack->pop_back();

}

void node::inc_rx(){
	rx+=5;
	update_matrices();
}


void node::inc_ry(){
	ry+=5;
	if(node_number==3 || node_number==4 || node_number==12 || node_number==14)
		ry=0;
	update_matrices();
}

void node::inc_rz(){
	rz+=5;
	if(node_number==3 || node_number==4 || node_number==12 || node_number==14)
		rz=0;
	update_matrices();
}

void node::dec_rx(){
	rx-=5;
	update_matrices();
}

void node::dec_ry(){
	ry-=5;
	if(node_number==3 || node_number==4 || node_number==12 || node_number==14)
		ry=0;
	update_matrices();
}

void node::dec_rz(){
	rz-=5;
	if(node_number==3 || node_number==4 || node_number==12 || node_number==14)
		rz=0;
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