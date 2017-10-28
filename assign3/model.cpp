#include "model.hpp"
#include <iostream>

#define PI 3.14159265

Model Model::draw_sphere(double radius, int Lats, int Longs)
{
  Model m;
  float lats,longs;

  float slices=(180/(float(Lats)*10))/2;
  float sectors=(180/(float(Longs)*10))/2;

  float l;

  for (lats = 0.0; lats <= PI; lats+=sectors)  
  {
    for(longs = 0.0; longs <= 2.0*PI; longs+=slices)
  	{
  	  float x = radius * sin(lats) * cos(longs);
  	  float y = radius * sin(lats) * sin(longs);
  	  float z = radius * cos(lats);
  	  // glm::vec4 pt(x, y, z, 1.0);

  	  m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);
  	  m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(z);
  	  m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
  	  m.num_vertex++;

  	  // v_colors[tri_idx] = white; v_positions[tri_idx] = pt; 
  	  // v_normals[tri_idx] = pt; tri_idx++;



  	  // w_colors[wire_idx] = black; w_positions[wire_idx] = pt; 
  	  // w_normals[wire_idx] = pt; wire_idx++;

  	  
  	  if(lats+sectors>PI)
  	    l=PI;
  	  else
  	    l=lats+sectors;
  	  x = radius * sin(l) * cos(longs);
  	  y = radius * sin(l) * sin(longs);
  	  z = radius * cos(l);
  	  // pt =glm::vec4(x, y, z, 1.0);
  	  // v_colors[tri_idx] = white; v_positions[tri_idx] = pt; 
  	  // v_normals[tri_idx] = pt; tri_idx++;

  	  m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);
  	  m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(z);
  	  m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
  	  m.num_vertex++;


  	  // w_colors[wire_idx] = black; w_positions[wire_idx] = pt; 
  	  // w_normals[wire_idx] = pt; wire_idx++;
  	}
  }

  // // To Complete the wireframe
  // for (lats = 0.0; lats <= PI; lats+=sectors)  
  // {
  //   for(longs = 0.0; longs <= 2.0*PI; longs+=slices)
  //   {
  // 	  float x = radius * sin(lats) * cos(longs);
  // 	  float y = radius * sin(lats) * sin(longs);
  // 	  float z = radius * cos(lats);
  // 	  glm::vec4 pt(x, y, z, 1.0);
  	  
  // 	  w_colors[wire_idx] = black; w_positions[wire_idx] = pt; 
  // 	  w_normals[wire_idx] = pt; wire_idx++;
  //   }
  // }
  return m;
}
