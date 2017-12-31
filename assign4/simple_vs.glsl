#version 330

in vec4 vPosition;
in vec4 vColor;
in vec2 texCoord;
in vec3 vNormal;

out vec3 normal;
out vec4 eye;
out vec4 COLOR;
out vec2 tex;

out vec4 ecPos;

uniform float switch1;
uniform float switch2;
uniform float switch3;

out float s1;
out float s2;
out float s3;

uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;
uniform int nodeNum;
void main (void)
{

    ecPos = uModelViewMatrix * vPosition;
    gl_Position = uModelViewMatrix * vPosition;
    normal = (normalMatrix * normalize(vNormal));
    eye = - (uModelViewMatrix * gl_Position);
    COLOR = vColor;
    s1 = switch1;
    s2 = switch2;
    s3 = switch3;
    tex = texCoord;
 }
