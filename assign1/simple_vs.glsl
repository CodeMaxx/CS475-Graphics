#version 400

in vec3 vp;
uniform mat4 transMatrix;

void main () 
{
  gl_Position = vec4 (vp, 1.0);
  gl_Position = transMatrix * gl_Position;
}
