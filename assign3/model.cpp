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

  	  m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
  	  m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(z);m.normal.push_back(1.0);
  	  m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
  	  m.num_vertex++;
  	  
  	  if(lats+sectors>PI)
  	    l=PI;
  	  else
  	    l=lats+sectors;
  	  x = radius * sin(l) * cos(longs);
  	  y = radius * sin(l) * sin(longs);
  	  z = radius * cos(l);

  	  m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
  	  m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(z);m.normal.push_back(1.0);
  	  m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
  	  m.num_vertex++;

  	}
  }
  return m;
}

Model Model::draw_cylinder(double radius, double height, int Lats)
{
  Model m;
  float lats,longs;

  float slices=(180/(float(Lats)*10))/2;

  float l;

  for (lats = 0.0; lats <= 2*PI; lats+=slices)  
  {
  	float x = 0.0;
	float y = 0.0;
	float z = 0.0;

  	m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
	m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(z);m.normal.push_back(1.0);
	m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
	m.num_vertex++;

	x = radius * cos(lats);
	y = radius * sin(lats);
	z = 0.0;

	m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
	m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(z);m.normal.push_back(1.0);
	m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
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
	m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
	m.num_vertex++; 

	x = radius * cos(lats);
	y = radius * sin(lats);
	z = height;

	m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
	m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(z);m.normal.push_back(1.0);
	m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
	m.num_vertex++;

	x = radius * cos(l);
	y = radius * sin(l);
	z = height;

	m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
	m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(z);m.normal.push_back(1.0);
	m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
	m.num_vertex++; 

	x = 0.0;
	y = 0.0;
	z = 0.0;

  	m.pts.push_back(x);m.pts.push_back(y);m.pts.push_back(z);m.pts.push_back(1.0);
	m.normal.push_back(x);m.normal.push_back(y);m.normal.push_back(z);m.normal.push_back(1.0);
	m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);m.color.push_back(1.0);
	m.num_vertex++;

  }
  return m;
}
