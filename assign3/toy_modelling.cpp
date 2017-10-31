#include "toy_modelling.hpp"
#include "texture.hpp"

void initShadersGL(void)
{
  std::string vertex_shader_file("simple_vs.glsl");
  std::string fragment_shader_file("simple_fs.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(cse::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(cse::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = cse::CreateProgramGL(shaderList);

}

void loadWoody()
{
  node* node1;
  GLuint skin = LoadTexture("images/skin.bmp",1600,1600);
  GLuint jeans = LoadTexture("images/jeans.bmp",256,256);
  GLuint boot = LoadTexture("images/boot1.bmp",480,317);
  GLuint face = LoadTexture("images/face.bmp",431,222);
  GLuint shirt = LoadTexture("images/shirt.bmp",256,256);
  //hip 0
  Model m = Model::draw_cuboid(1.0,0.6,0.5);
  node1 = new node(NULL,m,jeans);
  node1->change_parameters(0.0,0.0,-32.0,0.0,0.0,0.0);
  woody.push_back(node1);

  //left leg top 1
  m = Model::draw_cylinder(0.2,2.0,30);
  node1 = new node(woody[0],m,jeans);
  node1->change_parameters(0.3,0.0,0.0,90.0,0.0,0.0);
  woody.push_back(node1);

  //right leg top 2
  m = Model::draw_cylinder(0.2,2.0,30);
  node1 = new node(woody[0],m,jeans);
  node1->change_parameters(-0.3,0.0,0.0,90.0,0.0,0.0);
  woody.push_back(node1);

  //left leg bottom 3
  m = Model::draw_frustum(0.2,0.25,2.0,30);
  node1 = new node(woody[1],m,boot);
  node1->change_parameters(0,0,2.0,0,0.0,0.0);
  woody.push_back(node1);

  //right leg bottom 4
  m = Model::draw_frustum(0.2,0.25,2.0,30);
  node1 = new node(woody[2],m,boot);
  node1->change_parameters(0,0.0,2.0,0,0.0,0.0);
  woody.push_back(node1);

  //torso 5
  m = Model::draw_cuboid(1.0,1.5,0.5);
  node1 = new node(woody[0],m,shirt);
  node1->change_parameters(0,0.6,0,0,0.0,0.0);
  woody.push_back(node1);

  //shoulder 6
  m = Model::draw_cuboid(1.2,0.1,0.5);
  node1 = new node(woody[5],m,shirt);
  node1->change_parameters(0,1.5,0,0,0.0,0.0);
  woody.push_back(node1);

  //neck 7
  m = Model::draw_cylinder(0.3,0.3,30);
  node1 = new node(woody[6],m,skin);
  node1->change_parameters(0,0.1,0,-90,0.0,0.0);
  woody.push_back(node1);

  //head 8
  m = Model::draw_cylinder(0.5,1.8,30);
  node1 = new node(woody[7],m,face);
  node1->change_parameters(0,0,0.3,0,0.0,75.0);
  woody.push_back(node1);

  //hat bottom 9
  m = Model::draw_cylinder(0.8,0.1,30);
  node1 = new node(woody[8],m,boot);
  node1->change_parameters(0,0,1.8,0,0.0,0.0);
  woody.push_back(node1);

  //hat top 10
  m = Model::draw_cylinder(0.6,0.6,30);
  node1 = new node(woody[9],m,boot);
  node1->change_parameters(0,0,0.1,0,0.0,0.0);
  woody.push_back(node1);

  //left hand top 11
  m = Model::draw_cylinder(0.2,1.4,30);
  node1 = new node(woody[6],m,shirt);
  node1->change_parameters(0.6,0.05,0.0,90.0,30.0,0.0);
  woody.push_back(node1);

  //left hand bottom 12
  m = Model::draw_cylinder(0.2,1.4,30);
  node1 = new node(woody[11],m,shirt);
  node1->change_parameters(0.0,0,1.4,0.0,0,0.0);
  woody.push_back(node1);

  //right hand top 13
  m = Model::draw_cylinder(0.2,1.4,30);
  node1 = new node(woody[6],m,shirt);
  node1->change_parameters(-0.6,0.05,0.0,90.0,-30.0,0.0);
  woody.push_back(node1);

  //right hand bottom 14
  m = Model::draw_cylinder(0.2,1.4,30);
  node1 = new node(woody[13],m,shirt);
  node1->change_parameters(0.0,0,1.4,0.0,0,0.0);
  woody.push_back(node1);

  //left hand palm 15
  m = Model::draw_cuboid(0.5,0.5,0.2);
  node1 = new node(woody[12],m,skin);
  node1->change_parameters(0,0,1.4,90,0.0,0.0);
  woody.push_back(node1);

  //right hand palm 16
  m = Model::draw_cuboid(0.5,0.5,0.2);
  node1 = new node(woody[14],m,skin);
  node1->change_parameters(0,0,1.4,90,0.0,0.0);
  woody.push_back(node1);

  //left leg foot 17
  m = Model::draw_cuboid(0.5,0.7,0.2);
  node1 = new node(woody[3],m,boot);
  node1->change_parameters(0,0,2,0,0.0,0.0);
  woody.push_back(node1); 

  //right leg foot 18
  m = Model::draw_cuboid(0.5,0.7,0.2);
  node1 = new node(woody[4],m,boot);
  node1->change_parameters(0,0,2.0,0,0.0,0.0);
  woody.push_back(node1);

  curr_node = woody[0];
}

void loadStretch()
{
  node* node1;
  GLuint oct_leg = LoadTexture("images/oct_leg.bmp",960,638);
  GLuint oct_base = LoadTexture("images/stretch_base.bmp",672,295);

  //stretch base 19
  Model m = Model::draw_cylinder(0.8,2.3,30);
  node1 = new node(NULL,m,oct_base);
  node1->change_parameters(3.0,-0.6,-32.0,90,0.0,-110.0);
  stretch.push_back(node1);

  m = Model::draw_cylinder(0.2,2,30);
  node1 = new node(stretch[0],m,oct_leg);
  node1->change_parameters(0.8,0,2.3,0,60.0,0.0);
  stretch.push_back(node1);

  m = Model::draw_cylinder(0.2,2,30);
  node1 = new node(stretch[0],m,oct_leg);
  node1->change_parameters(-0.8,0,2.3,0,-60.0,0.0);
  stretch.push_back(node1);

  m = Model::draw_cylinder(0.2,2,30);
  node1 = new node(stretch[0],m,oct_leg);
  node1->change_parameters(0,0.8,2.3,-60.0,0.0,0.0);
  stretch.push_back(node1);

  m = Model::draw_cylinder(0.2,2,30);
  node1 = new node(stretch[0],m,oct_leg);
  node1->change_parameters(0,-0.8,2.3,60.0,0,0.0);
  stretch.push_back(node1);

  m = Model::draw_cylinder(0.2,2,30);
  node1 = new node(stretch[0],m,oct_leg);
  node1->change_parameters(0.8/sqrt(2),0.8/sqrt(2),2.3,-60.0/sqrt(2),60.0/sqrt(2),0.0);
  stretch.push_back(node1);

  m = Model::draw_cylinder(0.2,2,30);
  node1 = new node(stretch[0],m,oct_leg);
  node1->change_parameters(-0.8/sqrt(2),0.8/sqrt(2),2.3,-60.0/sqrt(2),-60.0/sqrt(2),0.0);
  stretch.push_back(node1);

  m = Model::draw_cylinder(0.2,2,30);
  node1 = new node(stretch[0],m,oct_leg);
  node1->change_parameters(0.8/sqrt(2),-0.8/sqrt(2),2.3,60.0/sqrt(2),60.0/sqrt(2),0.0);
  stretch.push_back(node1);

  //27
  m = Model::draw_cylinder(0.2,2,30);
  node1 = new node(stretch[0],m,oct_leg);
  node1->change_parameters(-0.8/sqrt(2),-0.8/sqrt(2),2.3,60.0/sqrt(2),-60.0/sqrt(2),0.0);
  stretch.push_back(node1);
}

void initVertexBufferGL(void)
{
  // getting the attributes from the shader program
  normalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
  viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" );
  vNormal = glGetAttribLocation( shaderProgram, "vNormal" );
  SWITCH1 = glGetUniformLocation( shaderProgram, "switch1" );
  SWITCH2 = glGetUniformLocation( shaderProgram, "switch2" );
  SWITCH3 = glGetUniformLocation( shaderProgram, "switch3" );
  texCoord = glGetAttribLocation( shaderProgram, "texCoord" );



  GLuint sky = LoadTexture("images/sky.bmp",960,540);
  GLuint splight = LoadTexture("images/all1.bmp",256,256);
  GLuint grass = LoadTexture("images/grass.bmp",736,736);
  
  loadWoody();
  loadStretch();

  Model m = Model::draw_ground();
  ground = new node(NULL,m,grass);
  ground->change_parameters(0,-12,-12,15,45,0.0);

  m = Model::draw_sphere(50.0,30,30);
  dome = new node(NULL,m,sky);
  dome->change_parameters(0,0,0,0,0.0,0.0);

  m = Model::draw_frustum(0.2,0.4,0.5,30);
  slight = new node(NULL,m,splight);
  slight->change_parameters(0,0,0,0,0.0,0.0);
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shaderProgram);

  if(switch1 > 0)
    glUniform1f(SWITCH1, 1.0);
  else
    glUniform1f(SWITCH1, 0.0);
  if(switch2 > 0)
    glUniform1f(SWITCH2, 1.0);
  else
    glUniform1f(SWITCH2, 0.0);
  if(switch3 > 0)
    glUniform1f(SWITCH3, 1.0);
  else
    glUniform1f(SWITCH3, 0.0);

  matrixStack1.clear();
  matrixStack2.clear();
  matrixStack3.clear();
  matrixStack4.clear();
  matrixStack5.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(1.5,0,0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7000.0);
    //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-12.0, 12.0, -12.0, 12.0, -5.0, 100.0);

  glm::mat4 id = glm::mat4(1.0f);

    //! Preparing global rotation matrix
  glm::mat4 xrot, yrot, zrot;
  xrot = glm::rotate(id, st.g_xtheta*st.rot_factor, glm::vec3(1.0f, 0.0f, 0.0f));
  yrot = glm::rotate(id, st.g_ytheta*st.rot_factor, glm::vec3(0.0f, 1.0f, 0.0f));
  zrot = glm::rotate(id, st.g_ztheta*st.rot_factor, glm::vec3(0.0f, 0.0f, 1.0f));
  global_rotation_matrix = xrot * yrot * zrot;

  glm::vec3 translation_amt(st.g_xtrans*st.trans_factor,st.g_ytrans*st.trans_factor,st.g_ztrans*st.trans_factor);
  global_translation_matrix = glm::translate(id, translation_amt);

  view_matrix = projection_matrix*lookat_matrix*global_rotation_matrix*global_translation_matrix;

  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  matrixStack1.push_back(view_matrix);
  matrixStack2.push_back(view_matrix);
  matrixStack3.push_back(view_matrix);
  matrixStack4.push_back(view_matrix);
  matrixStack5.push_back(view_matrix);

  woody[0]->render_tree(&matrixStack1);

  stretch[0]->render_tree(&matrixStack2);

  ground->render_tree(&matrixStack3);
  dome->render_tree(&matrixStack4);
  slight->render_tree(&matrixStack5);

}

int main(int argc, char** argv)
{
  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(cse::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  //We don't want the old OpenGL
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(640, 480, "CS475/CS675 OpenGL Framework", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }

  //! Make the window's context current
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, cse::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, cse::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  glfwSetWindowUserPointer(window, &st);
  // glfwSetMouseButtonCallback(window, cse::mouse_button_callback);

  //Initialize GL state
  cse::initGL();
  initShadersGL();
  initVertexBufferGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);

      // Poll for and process events
      glfwPollEvents();
    }

  glfwTerminate();
  return 0;
}

