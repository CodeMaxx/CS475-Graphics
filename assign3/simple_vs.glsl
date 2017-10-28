#version 400

in vec4 vPosition;
in vec4 vColor;
out vec4 color;
uniform mat4 transMatrix;

void main ()
{
	gl_Position = transMatrix * vPosition;
	color = vColor;
}
