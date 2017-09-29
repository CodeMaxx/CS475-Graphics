#version 400

in vec3 vPosition;
in vec3 vColor;
uniform int mode;
out vec4 color;
uniform mat4 transMatrix;

void main ()
{
	if(mode==0)
		gl_Position = vec4 (vPosition, 1.0);
	else
		gl_Position = vec4 (vPosition/1.0, 1.0);
	gl_Position = transMatrix * gl_Position;
	color = vec4 (vColor, 1.0);
}
