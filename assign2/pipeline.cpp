#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//! The pointer to the GLFW window
GLFWwindow* window;
GLuint shaderProgram;
GLuint vbo[3], vao;
GLuint frustum_vbo, frustum_vao;

//! State variable passed to GLFW
state st[3];

//! Tranformation matrices
GLuint transMatrix;
glm::mat4 rotation_matrix;
glm::mat4 translation_matrix;
glm::mat4 modelview_matrix;


void parser(void)
{
  int filenumber = 0;

  std::ifstream source;
  std::string filename = "myscene.scn";
  const char* tmp = filename.c_str();
  source.open(tmp);
  int input_state=0; //reading file state
  for(std::string line; std::getline(source, line);) {
    std::istringstream in(line);
    if(input_state==0){
      std::string rawfile;
      in>>rawfile;
      //read raw file
      std::ifstream raw_source;
      const char* raw_tmp = rawfile.c_str();
      raw_source.open(raw_tmp);
      for(std::string raw_line; std::getline(raw_source, raw_line);) {
            //input coordinate
        std::istringstream rawin(raw_line);
        float x,y,z;
        rawin >> x >> y >> z;
        st.model[filenumber].pts.push_back(x);
        st.model[filenumber].pts.push_back(y);
        st.model[filenumber].pts.push_back(z);
        st.model[filenumber].centroid.x = (st.model[filenumber].centroid.x*st.model[filenumber].num_vertex + x)/(st.model[filenumber].num_vertex + 1);
        st.model[filenumber].centroid.y = (st.model[filenumber].centroid.y*st.model[filenumber].num_vertex + y)/(st.model[filenumber].num_vertex + 1);
        st.model[filenumber].centroid.z = (st.model[filenumber].centroid.z*st.model[filenumber].num_vertex + z)/(st.model[filenumber].num_vertex + 1);
        st.model[filenumber].num_vertex++;
        //input color value
        float r,g,b;
        rawin >> r >> g >> b;
        st.model[filenumber].color.push_back(r);
        st.model[filenumber].color.push_back(g);
        st.model[filenumber].color.push_back(b);
        //push in VBO
        glBindBuffer(GL_ARRAY_BUFFER,vbo[filenumber]);
        glBufferData (GL_ARRAY_BUFFER, st.model[filenumber].pts.size() * sizeof (float) + st.model[filenumber].color.size() * sizeof (float), NULL, GL_STATIC_DRAW);
        glBufferSubData( GL_ARRAY_BUFFER, 0, st.model[filenumber].pts.size() * sizeof (float), &st.model[filenumber].pts[0] );
        glBufferSubData( GL_ARRAY_BUFFER, st.model[filenumber].pts.size() * sizeof (float),st.model[filenumber].color.size() * sizeof (float), &st.model[filenumber].color[0] );
      }
      input_state=1;
    }
    else if(input_state==1){
      in >> st.model[filenumber].xscale >> st.model[filenumber].yscale >> st.model[filenumber].zscale;
      input_state==2;
    }
    else if(input_state==2){
      in >> st.model[filenumber].xtheta >> st.model[filenumber].ytheta >> st.model[filenumber].ztheta;
      input_state==3;
    }
    else if(input_state==3){
      in >> st.model[filenumber].xtrans >> st.model[filenumber].ytrans >> st.model[filenumber].ztrans;
      filenumber++;
      if(filenumber==3) //all raw files parsed
        input_state==4;
      else //next raw file
        input_state==0;
    }
    else if(input_state==4){
      float x,y,z;
      in >> x >> y >> z;
      st.eye = glm::vec3(x,y,z);
      input_state==5;
    }
    else if(input_state==5){
      float x,y,z;
      in >> x >> y >> z;
      st.lookat_pt = glm::vec3(x,y,z);
      input_state==6;
    }
    else if(input_state==6){
      float x,y,z;
      in >> x >> y >> z;
      st.upvec = glm::vec3(x,y,z);
      input_state==7;
    }
    else if(input_state==7){
      in >> st.L >> st.R >> st.T >> st.B;
      input_state==8;
    }
    else if(input_state==8){
      in >> st.N >> st.F;
      input_state==9;
    }
  }
}

void initShadersGL(void)
{
  std::string vertex_shader_file("simple_vs.glsl");
  std::string fragment_shader_file("simple_fs.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(cse::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(cse::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = cse::CreateProgramGL(shaderList);

}

void initVertexBufferGL(void)
{
  //Ask GL for a Vertex Buffer Object (vbo)
  glGenBuffers (3, &vbo[0]);
  glGenBuffers(1,&frustum_vbo);
  //Set it as the current buffer to be used by binding it
  // glBindBuffer (GL_ARRAY_BUFFER, vbo);
  //Copy the points into the current buffer - 9 float values, start pointer and static data
  // glBufferData (GL_ARRAY_BUFFER, st.pts.size() * sizeof (float), &st.pts[0], GL_STATIC_DRAW);
  parser();

  //Ask GL for a Vertex Array Object (vao)
  glGenVertexArrays (1, &vao);
  glGenVertexArrays (1, &frustum_vao);
  //Set it as the current array to be used by binding it
  glBindVertexArray (vao);
  //Enable the vertex attribute
  glEnableVertexAttribArray (0);
  //This the layout of our first vertex buffer
  //"0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats
  glVertexAttribPointer (vao, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindVertexArray (frustum_vao);
  //Enable the vertex attribute
  glEnableVertexAttribArray (0);
  //This the layout of our first vertex buffer
  //"0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats
  glVertexAttribPointer (frustum_vao, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  transMatrix = glGetUniformLocation( shaderProgram, "transMatrix");
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shaderProgram);

  glBindVertexArray (vao);

  glm::mat4 id(1.0f);

  //! Prepare translation matrix
  glm::vec3 translation_amt(st.g_xtrans*st.trans_factor,st.g_ytrans*st.trans_factor,st.g_ztrans*st.trans_factor);
  translation_matrix = glm::translate(id, translation_amt);


  //! Prepare rotation matrix
  glm::mat4 xrot, yrot, zrot, to_centroid, back_centroid;
  to_centroid = glm::translate(id, -st.centroid);
  xrot = glm::rotate(id, st.g_xtheta*st.rot_factor, glm::vec3(1.0f, 0.0f, 0.0f));
  yrot = glm::rotate(id, st.g_ytheta*st.rot_factor, glm::vec3(0.0f, 1.0f, 0.0f));
  zrot = glm::rotate(id, st.g_ztheta*st.rot_factor, glm::vec3(0.0f, 0.0f, 1.0f));
  back_centroid = glm::translate(id, st.centroid);
  rotation_matrix = back_centroid * xrot * yrot * zrot * to_centroid;

  modelview_matrix = translation_matrix * rotation_matrix;

  // Bring back normal drawing when coming back to Modelling mode
  if(st.mode == 'M')
    modelview_matrix = id;

  glUniformMatrix4fv(transMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  glPointSize(5);

  GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

  GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(st.pts.size()*sizeof(float)) );

  glDrawArrays(GL_POINTS, 0, st.pts.size()/3);
  // Draw points 0-3 from the currently bound VAO with current in-use shader
  if(st.mode == 'I')
    glDrawArrays(GL_TRIANGLE_STRIP, 0, st.pts.size()/3);
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
  glfwSetMouseButtonCallback(window, cse::mouse_button_callback);

  //Initialize GL state
  cse::initGL();
  initShadersGL();
  initVertexBufferGL();

  std::cout << "Inspection Mode" << std::endl;

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

