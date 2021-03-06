#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

//! The pointer to the GLFW window
GLFWwindow* window;
GLuint shaderProgram;
GLuint vbo[3], vao;
GLuint axis_vbo;
GLuint frustum_vbo, frustum_vao;

//! State variable passed to GLFW
state st;

//! Tranformation matrices
GLuint transMatrix,mode;
glm::mat4 rotation_matrix;
glm::mat4 translation_matrix;
glm::mat4 scale_matrix;
glm::mat4 modelview_matrix;

int xl = 1,yl = 4,xh = 2,yh = 8;

// Get outcode for Cohen-Sutherland Line Clipping algo
int getoutcode(float x, float y){
  int code = 0;

  if(y > 1.0) code |= yh;
  if(y < -1.0) code |= yl;
  if(x < -1.0) code |= xl;
  if(x > 1.0) code |= xh;

  return code;
}

// Change the outer point to the intersection with the plane
void get_intersection(int outcode1, int outcode2, float &x1, float &y1, float &x2, float &y2) {
  while(1) {
    if(outcode1==0 && outcode2==0){
      break;
    }
    else if((outcode1 & outcode2) != 0){
      x1 = y1 = x2 = y2 = 0;
      break;
    }
    else {
      int x, y;
      float slope = (y2-y1)/(x2-x1);
      int outside;
      if(outcode1 == 0)
        outside = outcode2;
      else
        outside = outcode1;

      if(outside & yh) {
          x = x1+ (yh-y1)/slope;
          y = 1.0;
        }
        else if(outside & yl){
          x = x1 + (-1.0-y1)/slope;
          y = -1.0;
        }
        else if(outside & xl){
          x = -1.0;
          y = y1 + slope*(-1.0-x1);
        }else if(outside & xh){
          x = 1.0;
          y = y1 + slope*(1.0-x1);
        }
        if(outside == outcode1){
          x1 = x;
          y1 = y;
        }else{
          x2 = x;
          y2 = y;
        }
      }
    }
  }

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
      float pts[] = {0,0,0,0.2,0,0,0,0,0,0,0.2,0,0,0,0,0,0,0.2};
      float colors[] = {1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1};
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
  //1st vao
  glGenVertexArrays (1, &vao);
  glBindVertexArray (vao);
  //Enable the vertex attribute
  glEnableVertexAttribArray (0);
  glVertexAttribPointer (vao, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glGenBuffers (3, &vbo[0]);
  glGenBuffers (1, &axis_vbo);
  glGenBuffers(1,&frustum_vbo);

  //parse and add points to VBO
  parser();

  //2nd vao
  glGenVertexArrays (1, &frustum_vao);
  glBindVertexArray (frustum_vao);
  //Enable the vertex attribute
  glEnableVertexAttribArray (0);
  glVertexAttribPointer (frustum_vao, 3, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, frustum_vbo);

  float arr_pts[] = {0,0,0,st.R,st.T,-st.N,0,0,0,-st.L,st.T,-st.N,0,0,0,st.R,-st.B,-st.N,0,0,0,-st.L,-st.B,-st.N,st.R,st.T,-st.N,st.R,-st.B,-st.N,st.R,-st.B,-st.N,-st.L,-st.B,-st.N,-st.L,-st.B,-st.N,-st.L,st.T,-st.N,-st.L,st.T,-st.N,st.R,st.T,-st.N,st.R*st.F/st.N,st.T*st.F/st.N,-st.F,st.R*st.F/st.N,-st.B*st.F/st.N,-st.F,st.R*st.F/st.N,-st.B*st.F/st.N,-st.F,-st.L*st.F/st.N,-st.B*st.F/st.N,-st.F,-st.L*st.F/st.N,-st.B*st.F/st.N,-st.F,-st.L*st.F/st.N,st.T*st.F/st.N,-st.F,-st.L*st.F/st.N,st.T*st.F/st.N,-st.F,st.R*st.F/st.N,st.T*st.F/st.N,-st.F,st.R,st.T,-st.N,st.R*st.F/st.N,st.T*st.F/st.N,-st.F,st.R,-st.B,-st.N,st.R*st.F/st.N,-st.B*st.F/st.N,-st.F,-st.L,-st.B,-st.N,-st.L*st.F/st.N,-st.B*st.F/st.N,-st.F,-st.L,st.T,-st.N,-st.L*st.F/st.N,st.T*st.F/st.N,-st.F,0,0,0};

  st.frustum_pts.insert(st.frustum_pts.end(), arr_pts, arr_pts+sizeof(arr_pts)/sizeof(*arr_pts));

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
  glm::mat4 id(1.0f);
  glPointSize(5);
  glLineWidth(5);

  // glm::mat4 wcs_to_vcs_matrix = glm::lookAt(st.eye, st.lookat_pt, st.upvec);
  glm::mat4 wcs_to_vcs_matrix = st.wcs_to_vcs();
  glm::mat4 vcs_to_ccs_matrix = st.vcs_to_ccs();
  glm::mat4 ndcs_to_dcs = st.ndcs_to_dcs();

  glm::mat4 wcs_to_vcs_inverse = glm::inverse(wcs_to_vcs_matrix);

  // Preparing global translation matrix
  glm::vec3 translation_amt(st.g_xtrans*st.trans_factor,st.g_ytrans*st.trans_factor,st.g_ztrans*st.trans_factor);
  translation_matrix = glm::translate(id, translation_amt);

  //! Preparing global rotation matrix
  glm::mat4 xrot, yrot, zrot;
  xrot = glm::rotate(id, st.g_xtheta*st.rot_factor, glm::vec3(1.0f, 0.0f, 0.0f));
  yrot = glm::rotate(id, st.g_ytheta*st.rot_factor, glm::vec3(0.0f, 1.0f, 0.0f));
  zrot = glm::rotate(id, st.g_ztheta*st.rot_factor, glm::vec3(0.0f, 0.0f, 1.0f));
  rotation_matrix = xrot * yrot * zrot;

  glm::mat4 view_matrix = st.view_matrix();
  glm::mat4 global_matrix = view_matrix* rotation_matrix * translation_matrix;

  for(int i=0;i<3;i++){
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);

    //! Prepare translation matrix
    glm::vec3 translation_amt(st.model[i].xtrans, st.model[i].ytrans, st.model[i].ztrans);
    translation_matrix = glm::translate(id, translation_amt);

    //! Prepare rotation matrix
    glm::mat4 xrot, yrot, zrot, to_centroid, back_centroid;
    to_centroid = glm::translate(id, -st.model[i].centroid);
    xrot = glm::rotate(id, glm::radians(st.model[i].xtheta), glm::vec3(1.0f, 0.0f, 0.0f));
    yrot = glm::rotate(id, glm::radians(st.model[i].ytheta), glm::vec3(0.0f, 1.0f, 0.0f));
    zrot = glm::rotate(id, glm::radians(st.model[i].ztheta), glm::vec3(0.0f, 0.0f, 1.0f));
    back_centroid = glm::translate(id, st.model[i].centroid);
    rotation_matrix = back_centroid * xrot * yrot * zrot * to_centroid;

    //prepare scaling matrix
    glm::vec3 scale_amt(st.model[i].xscale,st.model[i].yscale,st.model[i].zscale);
    scale_matrix = glm::scale(id, scale_amt);

    glm::mat4 local_matrix = translation_matrix * rotation_matrix * scale_matrix;

    modelview_matrix = global_matrix * local_matrix;

    if(st.mode=='1')
      modelview_matrix = global_matrix * wcs_to_vcs_matrix * local_matrix;
    else if(st.mode == '2' || st.mode == '3')
      modelview_matrix = global_matrix * vcs_to_ccs_matrix * wcs_to_vcs_matrix * local_matrix;
    else if(st.mode=='4')
      modelview_matrix = global_matrix * ndcs_to_dcs * vcs_to_ccs_matrix * wcs_to_vcs_matrix * local_matrix;

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

  modelview_matrix = global_matrix;

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

  modelview_matrix = global_matrix * wcs_to_vcs_inverse;

  if(st.mode=='1')
    modelview_matrix = global_matrix;
  else if(st.mode=='2' || st.mode=='3')
    modelview_matrix = global_matrix * vcs_to_ccs_matrix;
  else if(st.mode=='4')
    modelview_matrix = global_matrix * ndcs_to_dcs * vcs_to_ccs_matrix;

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

