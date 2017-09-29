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
GLuint axis_vbo;
GLuint frustum_vbo, frustum_vao;

//! State variable passed to GLFW
state st;

//! Tranformation matrices
GLuint transMatrix;
glm::mat4 rotation_matrix;
glm::mat4 translation_matrix;
glm::mat4 scale_matrix;
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
      input_state=2;
    }
    else if(input_state==2){
      in >> st.model[filenumber].xtheta >> st.model[filenumber].ytheta >> st.model[filenumber].ztheta;
      input_state=3;
    }
    else if(input_state==3){
      in >> st.model[filenumber].xtrans >> st.model[filenumber].ytrans >> st.model[filenumber].ztrans;
      filenumber++;
      if(filenumber==3) //all raw files parsed
        input_state=4;
      else //next raw file
        input_state=0;
    }
    else if(input_state==4){
      float pts[] = {0,0,0,1,1,1,0,0,0,0,0.2,0,0,0,0,0,0,0.2};
      float colors[] = {0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1};
      st.axis_pts.insert(st.axis_pts.end(), pts, pts + sizeof(pts)/sizeof(*pts));
      st.axis_color.insert(st.axis_color.end(), colors, colors + sizeof(colors)/sizeof(*colors));
      glBindBuffer(GL_ARRAY_BUFFER, axis_vbo);
      glBufferData (GL_ARRAY_BUFFER, st.axis_pts.size() * sizeof (float) + st.axis_color.size() * sizeof (float), NULL, GL_STATIC_DRAW);
      glBufferSubData( GL_ARRAY_BUFFER, 0, st.axis_pts.size() * sizeof (float), &st.axis_pts[0] );
      glBufferSubData( GL_ARRAY_BUFFER, st.axis_pts.size() * sizeof (float),st.axis_color.size() * sizeof (float), &st.axis_color[0] );
      float x,y,z;
      in >> x >> y >> z;
      st.eye = glm::vec3(x,y,z);
      input_state=5;
    }
    else if(input_state==5){
      float x,y,z;
      in >> x >> y >> z;
      st.lookat_pt = glm::vec3(x,y,z);
      input_state=6;
    }
    else if(input_state==6){
      float x,y,z;
      in >> x >> y >> z;
      st.upvec = glm::vec3(x,y,z);
      input_state=7;
    }
    else if(input_state==7){
      in >> st.L >> st.R >> st.T >> st.B;
      input_state=8;
    }
    else if(input_state==8){
      in >> st.N >> st.F;
      input_state=9;
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

  glGenVertexArrays (1, &vao);
  //Set it as the current array to be used by binding it
  glBindVertexArray (vao);
  //Enable the vertex attribute
  glEnableVertexAttribArray (0);
  //This the layout of our first vertex buffer
  //"0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats
  glVertexAttribPointer (vao, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  //Ask GL for a Vertex Buffer Object (vbo)
  glGenBuffers (3, &vbo[0]);
  glGenBuffers(1,&frustum_vbo);
  //Set it as the current buffer to be used by binding it
  // glBindBuffer (GL_ARRAY_BUFFER, vbo);
  //Copy the points into the current buffer - 9 float values, start pointer and static data
  // glBufferData (GL_ARRAY_BUFFER, st.pts.size() * sizeof (float), &st.pts[0], GL_STATIC_DRAW);
  parser();

  //Ask GL for a Vertex Array Object (vao)
  glGenVertexArrays (1, &frustum_vao);

  glBindVertexArray (frustum_vao);
  //Enable the vertex attribute
  glEnableVertexAttribArray (0);
  //This the layout of our first vertex buffer
  //"0" means define the layout for attribute number 0. "3" means that the variables are vec3 made from every 3 floats
  glVertexAttribPointer (frustum_vao, 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ARRAY_BUFFER, frustum_vbo);

  float arr_pts[] = {0,0,0,st.R,st.T,-st.N,0,0,0,-st.L,st.T,-st.N,0,0,0,st.R,-st.B,-st.N,0,0,0,-st.L,-st.B,-st.N,st.R,st.T,-st.N,st.R,-st.B,-st.N,st.R,-st.B,-st.N,-st.L,-st.B,-st.N,-st.L,-st.B,-st.N,-st.L,st.T,-st.N,-st.L,st.T,-st.N,st.R,st.T,-st.N,st.R*st.F/st.N,st.T*st.F/st.N,-st.F,st.R*st.F/st.N,-st.B*st.F/st.N,-st.F,st.R*st.F/st.N,-st.B*st.F/st.N,-st.F,-st.L*st.F/st.N,-st.B*st.F/st.N,-st.F,-st.L*st.F/st.N,-st.B*st.F/st.N,-st.F,-st.L*st.F/st.N,st.T*st.F/st.N,-st.F,-st.L*st.F/st.N,st.T*st.F/st.N,-st.F,st.R*st.F/st.N,st.T*st.F/st.N,-st.F,st.R,st.T,-st.N,st.R*st.F/st.N,st.T*st.F/st.N,-st.F,st.R,-st.B,-st.N,st.R*st.F/st.N,-st.B*st.F/st.N,-st.F,-st.L,-st.B,-st.N,-st.L*st.F/st.N,-st.B*st.F/st.N,-st.F,-st.L,st.T,-st.N,-st.L*st.F/st.N,st.T*st.F/st.N,-st.F,0,0,0};

  for(int i = 0; i < sizeof(arr_pts)/sizeof(*arr_pts)-3; i++){
    if(i%3 == 0)
      st.frustum_centroid.x += arr_pts[i];
    else if(i%3 == 1)
      st.frustum_centroid.y += arr_pts[i];
    else
      st.frustum_centroid.z += arr_pts[i];
  }

  st.frustum_centroid.x /= (sizeof(arr_pts)/sizeof(*arr_pts)/3-1);
  st.frustum_centroid.y /= (sizeof(arr_pts)/sizeof(*arr_pts)/3-1);
  st.frustum_centroid.z /= (sizeof(arr_pts)/sizeof(*arr_pts)/3-1);

  st.frustum_pts.insert(st.frustum_pts.end(), arr_pts, arr_pts+sizeof(arr_pts)/sizeof(*arr_pts));

  std::cout << st.frustum_pts.size() << "blablabla" << std::endl;

  for(int i = 0; i < 8; i++){
    st.frustum_color.push_back(1);
    st.frustum_color.push_back(0);
    st.frustum_color.push_back(1);
  }

  for(int i = 0; i < 24; i++){
    st.frustum_color.push_back(0);
    st.frustum_color.push_back(1);
    st.frustum_color.push_back(1);
  }
  // pushing red for eye
  st.frustum_color.push_back(1);
  st.frustum_color.push_back(0);
  st.frustum_color.push_back(0);

  glBufferData (GL_ARRAY_BUFFER, st.frustum_pts.size() * sizeof (float) + st.frustum_color.size() * sizeof (float), NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, st.frustum_pts.size() * sizeof (float), &st.frustum_pts[0] );
  glBufferSubData( GL_ARRAY_BUFFER, st.frustum_pts.size() * sizeof (float),st.frustum_color.size() * sizeof (float), &st.frustum_color[0] );

  transMatrix = glGetUniformLocation( shaderProgram, "transMatrix");
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(shaderProgram);

  glBindVertexArray (vao);

  // Bring back normal drawing when coming back to Modelling mode
  // if(st.mode == 'M')
  //   modelview_matrix = id;
  glm::mat4 id(1.0f);
  glPointSize(5);
  glLineWidth(5);

  glm::mat4 wcs_to_vcs_matrix = glm::lookAt(st.eye, st.lookat_pt, st.upvec);

  glm::mat4 wcs_to_vcs_inverse = glm::inverse(wcs_to_vcs_matrix);

  for(int i=0;i<3;i++){
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);

    //! Prepare translation matrix
    glm::vec3 translation_amt(st.g_xtrans*st.trans_factor+st.model[i].xtrans,st.g_ytrans*st.trans_factor+st.model[i].ytrans,st.g_ztrans*st.trans_factor+st.model[i].ztrans);
    translation_matrix = glm::translate(id, translation_amt);


    //! Prepare rotation matrix
    glm::mat4 xrot, yrot, zrot, to_centroid, back_centroid;
    to_centroid = glm::translate(id, -st.model[i].centroid);
    xrot = glm::rotate(id, glm::radians(st.model[i].xtheta), glm::vec3(1.0f, 0.0f, 0.0f));
    yrot = glm::rotate(id, glm::radians(st.model[i].ytheta), glm::vec3(0.0f, 1.0f, 0.0f));
    zrot = glm::rotate(id, glm::radians(st.model[i].ztheta), glm::vec3(0.0f, 0.0f, 1.0f));
    back_centroid = glm::translate(id, st.model[i].centroid);
    rotation_matrix = back_centroid * xrot * yrot * zrot * to_centroid;

    xrot = glm::rotate(id, st.g_xtheta*st.rot_factor, glm::vec3(1.0f, 0.0f, 0.0f));
    yrot = glm::rotate(id, st.g_ytheta*st.rot_factor, glm::vec3(0.0f, 1.0f, 0.0f));
    zrot = glm::rotate(id, st.g_ztheta*st.rot_factor, glm::vec3(0.0f, 0.0f, 1.0f));

    rotation_matrix = xrot * yrot * zrot * rotation_matrix;

    //prepare scaling matrix
    glm::vec3 scale_amt(st.g_scale*st.scale_factor*st.model[i].xscale,st.g_scale*st.scale_factor*st.model[i].yscale,st.g_scale*st.scale_factor*st.model[i].zscale);
    scale_matrix = glm::scale(id, scale_amt);
    // std::cout<<st.model[i].xscale<<std::endl;
    modelview_matrix = translation_matrix * rotation_matrix * scale_matrix;

    if(st.mode=='1')
      modelview_matrix = modelview_matrix * wcs_to_vcs_matrix;

    glUniformMatrix4fv(transMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

    GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

    GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(st.model[i].pts.size()*sizeof(float)) );

    glDrawArrays(GL_TRIANGLE_STRIP, 0, st.model[i].pts.size()/3);
  }

  // Draw Axis
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, axis_vbo);
  glUniformMatrix4fv(transMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  glm::vec3 translation_amt(st.g_xtrans*st.trans_factor, st.g_ytrans*st.trans_factor, st.g_ztrans*st.trans_factor);
  translation_matrix = glm::translate(id, translation_amt);

  //! Prepare rotation matrix
  glm::mat4 xrot, yrot, zrot;
  xrot = glm::rotate(id, st.g_xtheta*st.rot_factor, glm::vec3(1.0f, 0.0f, 0.0f));
  yrot = glm::rotate(id, st.g_ytheta*st.rot_factor, glm::vec3(0.0f, 1.0f, 0.0f));
  zrot = glm::rotate(id, st.g_ztheta*st.rot_factor, glm::vec3(0.0f, 0.0f, 1.0f));
  rotation_matrix = xrot * yrot * zrot;

  //prepare scaling matrix
  glm::vec3 scale_amt(st.g_scale*st.scale_factor, st.g_scale*st.scale_factor, st.g_scale*st.scale_factor);
  scale_matrix = glm::scale(id, scale_amt);


  modelview_matrix = translation_matrix * rotation_matrix * scale_matrix;

  if(st.mode=='1')
      modelview_matrix = modelview_matrix * wcs_to_vcs_matrix;

  glUniformMatrix4fv(transMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  GLuint vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

  GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" );
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(st.axis_pts.size()*sizeof(float)) );

  glDrawArrays(GL_LINES, 0, st.axis_pts.size()/3);


// Draw Frustum

  glBindVertexArray (frustum_vao);
  glBindBuffer(GL_ARRAY_BUFFER, frustum_vbo);


  modelview_matrix = translation_matrix * rotation_matrix * scale_matrix * wcs_to_vcs_inverse;
  glUniformMatrix4fv(transMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));

  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

  vColor = glGetAttribLocation( shaderProgram, "vColor" );
  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(st.frustum_pts.size()*sizeof(float)) );

  glDrawArrays(GL_LINES, 0, st.frustum_pts.size()/3-1);
  glDrawArrays(GL_POINTS, st.frustum_pts.size()/3-1, st.frustum_pts.size()/3);

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

