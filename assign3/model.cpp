#include "model.hpp"

#define PI 3.14159265

Model Model::draw_sphere(double radius, int Lats, int Longs)
{
  Model m;
  float lats,longs;

  float slices=(180/(float(Lats)*10))/2;
  float sectors=(180/(float(Longs)*10))/2;

  float l;
  float last_lat1=0.0, last_lat2=0.0, last_long=0.0;

  for (lats = 0.0; lats <= PI; lats+=sectors)
  {
    for(longs = 0.0; longs <= 2.0*PI; longs+=slices)
  	{
      //last 1
      float x = radius * sin(last_lat1) * cos(last_long);
      float y = radius * sin(last_lat1) * sin(last_long);
      float z = radius * cos(last_lat1);

      m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
      m.normal.push_back(-x);m.normal.push_back(-y);m.normal.push_back(-z);m.normal.push_back(1.0);
      m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
      m.texture.push_back(100*last_lat1/PI);m.texture.push_back(100*last_long/(2*PI));
      m.num_vertex++;

      //last 2
      x = radius * sin(last_lat2) * cos(last_long);
      y = radius * sin(last_lat2) * sin(last_long);
      z = radius * cos(last_lat2);

      m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
      m.normal.push_back(-x);m.normal.push_back(-y);m.normal.push_back(-z);m.normal.push_back(1.0);
      m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
      m.texture.push_back(100*last_lat2/PI);m.texture.push_back(100*last_long/(2*PI));
      m.num_vertex++;

      // now 3
  	  x = radius * sin(lats) * cos(longs);
  	  y = radius * sin(lats) * sin(longs);
  	  z = radius * cos(lats);

  	  m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
  	  m.normal.push_back(-x);m.normal.push_back(-y);m.normal.push_back(-z);m.normal.push_back(1.0);
  	  m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
      m.texture.push_back(100*lats/PI);m.texture.push_back(100*longs/(2*PI));
  	  m.num_vertex++;

      //last 2
      x = radius * sin(last_lat2) * cos(last_long);
      y = radius * sin(last_lat2) * sin(last_long);
      z = radius * cos(last_lat2);

      m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
      m.normal.push_back(-x);m.normal.push_back(-y);m.normal.push_back(-z);m.normal.push_back(1.0);
      m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
      m.texture.push_back(100*last_lat2/PI);m.texture.push_back(100*last_long/(2*PI));
      m.num_vertex++;

      x = radius * sin(lats) * cos(longs);
      y = radius * sin(lats) * sin(longs);
      z = radius * cos(lats);

      m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
      m.normal.push_back(-x);m.normal.push_back(-y);m.normal.push_back(-z);m.normal.push_back(1.0);
      m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
      m.texture.push_back(100*lats/PI);m.texture.push_back(100*longs/(2*PI));
      m.num_vertex++;
      last_lat1 = lats;
      last_long = longs;

  	  if(lats+sectors>PI)
  	    l=PI;
  	  else
  	    l=lats+sectors;
  	  x = radius * sin(l) * cos(longs);
  	  y = radius * sin(l) * sin(longs);
  	  z = radius * cos(l);


  	  m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
  	  m.normal.push_back(-x);m.normal.push_back(-y);m.normal.push_back(-z);m.normal.push_back(1.0);
  	  m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
      m.texture.push_back(100*l/PI);m.texture.push_back(100*longs/(2*PI));
  	  m.num_vertex++;
      last_lat2 = l;
  	}
  }
  m.type=1;
  return m;
}

void quad(Model* m, glm::vec4 positions[], glm::vec4 normals[],int face, int a, int b, int c, int d)
{
  a--;b--;c--;d--;
  m->pts.push_back(positions[a][0]);m->pts.push_back(positions[a][1]);m->pts.push_back(positions[a][2]);m->pts.push_back(positions[a][3]);
  m->pts.push_back(positions[b][0]);m->pts.push_back(positions[b][1]);m->pts.push_back(positions[b][2]);m->pts.push_back(positions[b][3]);
  m->pts.push_back(positions[c][0]);m->pts.push_back(positions[c][1]);m->pts.push_back(positions[c][2]);m->pts.push_back(positions[c][3]);
  m->pts.push_back(positions[b][0]);m->pts.push_back(positions[b][1]);m->pts.push_back(positions[b][2]);m->pts.push_back(positions[b][3]);
  m->pts.push_back(positions[c][0]);m->pts.push_back(positions[c][1]);m->pts.push_back(positions[c][2]);m->pts.push_back(positions[c][3]);
  m->pts.push_back(positions[d][0]);m->pts.push_back(positions[d][1]);m->pts.push_back(positions[d][2]);m->pts.push_back(positions[d][3]);
  m->texture.push_back(0.0);m->texture.push_back(0.0);
  m->texture.push_back(1.0);m->texture.push_back(0.0);
  m->texture.push_back(0.0);m->texture.push_back(1.0);
  m->texture.push_back(1.0);m->texture.push_back(0.0);
  m->texture.push_back(0.0);m->texture.push_back(1.0);
  m->texture.push_back(1.0);m->texture.push_back(1.0);
  for(int i=0;i<6;i++){
     m->normal.push_back(normals[face][0]);m->normal.push_back(normals[face][1]);m->normal.push_back(normals[face][2]);m->normal.push_back(normals[face][3]);
     m->color.push_back(0.5);m->color.push_back(0.0);m->color.push_back(0.5);m->color.push_back(1.0);
  }
  m->num_vertex+=6;
}


Model Model::draw_cuboid(double xlength, double ylength, double zlength)
{
  Model m;
  glm::vec4 positions[8] = {
    glm::vec4(-xlength/2, ylength,zlength/2, 1.0),
    glm::vec4(xlength/2, ylength, zlength/2, 1.0),
    glm::vec4(-xlength/2, 0, zlength/2, 1.0),
    glm::vec4(xlength/2, 0,zlength/2, 1.0),
    glm::vec4(-xlength/2, ylength, -zlength/2, 1.0),
    glm::vec4(xlength/2, ylength, -zlength/2, 1.0),
    glm::vec4(-xlength/2, 0, -zlength/2, 1.0),
    glm::vec4(xlength/2, 0, -zlength/2, 1.0)
  };
  glm::vec4 normals[6] = {
    glm::vec4(0, 0,zlength, 1.0),
    glm::vec4(-xlength, 0, 0, 1.0),
    glm::vec4(0, 0, -zlength, 1.0),
    glm::vec4(xlength, 0,0, 1.0),
    glm::vec4(0, ylength, 0,1.0),
    glm::vec4(0, -ylength, 0, 1.0),
  };

  quad(&m,positions,normals,0,1,2,3,4);
  quad(&m,positions,normals,1,5,1,7,3);
  quad(&m,positions,normals,2,5,6,7,8);
  quad(&m,positions,normals,3,2,6,4,8);
  quad(&m,positions,normals,4,1,2,5,6);
  quad(&m,positions,normals,5,3,4,7,8);
  m.type=3;
  return m;
}

Model Model::draw_ground()
{
  Model m;
  glm::vec4 positions[4] = {
    glm::vec4(-50,2.0, -50.0, 1.0),
    glm::vec4(50, 2.0, -50.0, 1.0),
    glm::vec4(-50, 2.0, 50, 1.0),
    glm::vec4(50, 2.0,50, 1.0),

  };
  glm::vec4 normals[1] = {
    glm::vec4(0,1.0,0, 1.0),
  };
  quad(&m,positions,normals,0,1,2,3,4);
  m.type=1;
  return m;
}

Model Model::draw_cylinder(double radius, double height, int Lats)
{
  Model m;
  float lats,longs;

  float slices=(180/(float(Lats)*10))/2;

  float l;
  // uppper circle
  for (lats = 0.0; lats <= 2*PI; lats+=slices)  
  {
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(0);m.normal.push_back(0);m.normal.push_back(-height);m.normal.push_back(1.0);
    m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(0.5);m.texture.push_back(0.5);
    m.num_vertex++;

    x = radius * cos(lats);
    y = radius * sin(lats);
    z = 0.0;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(0);m.normal.push_back(0);m.normal.push_back(-height);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(0.5+0.5*cos(lats));m.texture.push_back(0.5+0.5*sin(lats));
    m.num_vertex++;

    if(lats+slices>2*PI)
    l=2*PI;
    else
    l=lats+slices;

    x = radius * cos(l);
    y = radius * sin(l);
    z = 0.0;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(0);m.normal.push_back(0);m.normal.push_back(-height);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);
    m.texture.push_back(0.5+0.5*cos(l));m.texture.push_back(0.5+0.5*sin(l));
    m.num_vertex++;   

  }
  //lateral surface
  for (lats = 0.0; lats <= 2*PI; lats+=slices)  
  {
  	float x = 0.0;
  	float y = 0.0;
  	float z = 0.0;

  	x = radius * cos(lats);
  	y = radius * sin(lats);
  	z = 0.0;

  	m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
  	m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(z);m.normal.push_back(1.0);
  	m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(lats/(2*PI));m.texture.push_back(0);
  	m.num_vertex++;

  	if(lats+slices>2*PI)
  	l=2*PI;
  	else
  	l=lats+slices;

  	x = radius * cos(l);
  	y = radius * sin(l);
  	z = 0.0;

  	m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
  	m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(z);m.normal.push_back(1.0);
  	m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);
    m.texture.push_back(l/(2*PI));m.texture.push_back(0);
  	m.num_vertex++; 

  	x = radius * cos(lats);
  	y = radius * sin(lats);
  	z = height;

  	m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
  	m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(0);m.normal.push_back(1.0);
  	m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(lats/(2*PI));m.texture.push_back(1);
  	m.num_vertex++;

    if(lats+slices>2*PI)
    l=2*PI;
    else
    l=lats+slices;

    x = radius * cos(l);
    y = radius * sin(l);
    z = 0.0;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(0);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);
    m.texture.push_back(l/(2*PI));m.texture.push_back(0);
    m.num_vertex++; 

    x = radius * cos(lats);
    y = radius * sin(lats);
    z = height;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(0);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(lats/(2*PI));m.texture.push_back(1);
    m.num_vertex++;

    if(lats+slices>2*PI)
    l=2*PI;
    else
    l=lats+slices;

  	x = radius * cos(l);
  	y = radius * sin(l);
  	z = height;

  	m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
  	m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(0);m.normal.push_back(1.0);
  	m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(l/(2*PI));m.texture.push_back(1);
  	m.num_vertex++;

  }
    // lower circle
  for (lats = 0.0; lats <= 2*PI; lats+=slices)  
  {
    float x = 0.0;
    float y = 0.0;
    float z = height;
    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(0);m.normal.push_back(0);m.normal.push_back(height);m.normal.push_back(1.0);
    m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(0.5);m.texture.push_back(0.5);
    m.num_vertex++;

    x = radius * cos(lats);
    y = radius * sin(lats);
    z = height;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(0);m.normal.push_back(0);m.normal.push_back(height);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(0.5+0.5*cos(lats));m.texture.push_back(0.5+0.5*sin(lats));
    m.num_vertex++;

    if(lats+slices>2*PI)
    l=2*PI;
    else
    l=lats+slices;

    x = radius * cos(l);
    y = radius * sin(l);
    z = height;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(0);m.normal.push_back(0);m.normal.push_back(height);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);
    m.texture.push_back(0.5+0.5*cos(l));m.texture.push_back(0.5+0.5*sin(l));
    m.num_vertex++;   

  }
  m.type=2;
  return m;
}

Model Model::draw_frustum(double radius1, double radius2, double height, int Lats)
{

  Model m;
  float lats,longs;

  float slices=(180/(float(Lats)*10))/2;

  float l;
  // uppper circle
  for (lats = 0.0; lats <= 2*PI; lats+=slices)  
  {
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;
    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(0);m.normal.push_back(0);m.normal.push_back(-height);m.normal.push_back(1.0);
    m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(0.5);m.texture.push_back(0.5);
    m.num_vertex++;

    x = radius1 * cos(lats);
    y = radius1 * sin(lats);
    z = 0.0;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(0);m.normal.push_back(0);m.normal.push_back(-height);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(0.5+0.5*cos(lats));m.texture.push_back(0.5+0.5*sin(lats));
    m.num_vertex++;

    if(lats+slices>2*PI)
    l=2*PI;
    else
    l=lats+slices;

    x = radius1 * cos(l);
    y = radius1 * sin(l);
    z = 0.0;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(0);m.normal.push_back(0);m.normal.push_back(-height);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);
    m.texture.push_back(0.5+0.5*cos(l));m.texture.push_back(0.5+0.5*sin(l));
    m.num_vertex++;   

  }
  //lateral surface
  for (lats = 0.0; lats <= 2*PI; lats+=slices)  
  {
    float x = 0.0;
    float y = 0.0;
    float z = 0.0;

    x = radius1 * cos(lats);
    y = radius1 * sin(lats);
    z = 0.0;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(radius2*(radius2-radius1)/height);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(lats/(2*PI));m.texture.push_back(0);
    m.num_vertex++;

    if(lats+slices>2*PI)
    l=2*PI;
    else
    l=lats+slices;

    x = radius1 * cos(l);
    y = radius1 * sin(l);
    z = 0.0;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(radius2*(radius2-radius1)/height);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);
    m.texture.push_back(l/(2*PI));m.texture.push_back(0);
    m.num_vertex++; 

    x = radius2 * cos(lats);
    y = radius2 * sin(lats);
    z = height;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(radius2*(radius2-radius1)/height);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(lats/(2*PI));m.texture.push_back(1);
    m.num_vertex++;

    if(lats+slices>2*PI)
    l=2*PI;
    else
    l=lats+slices;

    x = radius1 * cos(l);
    y = radius1 * sin(l);
    z = 0.0;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(radius2*(radius2-radius1)/height);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);
    m.texture.push_back(l/(2*PI));m.texture.push_back(0);
    m.num_vertex++; 

    x = radius2 * cos(lats);
    y = radius2 * sin(lats);
    z = height;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(radius2*(radius2-radius1)/height);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(lats/(2*PI));m.texture.push_back(1);
    m.num_vertex++;

    if(lats+slices>2*PI)
    l=2*PI;
    else
    l=lats+slices;

    x = radius2 * cos(l);
    y = radius2 * sin(l);
    z = height;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(radius2*(radius2-radius1)/height);m.normal.push_back(1.0);
    m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(l/(2*PI));m.texture.push_back(1);
    m.num_vertex++; 


  }
    // lower circle
  for (lats = 0.0; lats <= 2*PI; lats+=slices)  
  {
    float x = 0.0;
    float y = 0.0;
    float z = height;
    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(0);m.normal.push_back(0);m.normal.push_back(height);m.normal.push_back(1.0);
    m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(0.5);m.texture.push_back(0.5);
    m.num_vertex++;

    x = radius2 * cos(lats);
    y = radius2 * sin(lats);
    z = height;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(0);m.normal.push_back(0);m.normal.push_back(height);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);m.color.push_back(1.0);
    m.texture.push_back(0.5+0.5*cos(lats));m.texture.push_back(0.5+0.5*sin(lats));
    m.num_vertex++;

    if(lats+slices>2*PI)
    l=2*PI;
    else
    l=lats+slices;

    x = radius2 * cos(l);
    y = radius2 * sin(l);
    z = height;

    m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
    m.normal.push_back(0);m.normal.push_back(0);m.normal.push_back(height);m.normal.push_back(1.0);
    m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(0.5);m.color.push_back(1.0);
    m.texture.push_back(0.5+0.5*cos(l));m.texture.push_back(0.5+0.5*sin(l));
    m.num_vertex++;

  }
  m.type=2;
  return m;
}
