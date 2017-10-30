#version 330

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

out vec3 normal;
out vec4 eye;
out vec4 COLOR;

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
void main (void)
{

  // // Defining Materials
  // vec4 diffuse = vec4(0.5, 0.0, 0.0, 1.0);
  // vec4 ambient = vec4(0.1, 0.0, 0.0, 1.0);
  // vec4 specular = vec4(1.0, 0.5, 0.5, 1.0);
  // float shininess = 0.05;
  // vec4 spec = vec4(0.0);

  // // Defining Light
  // vec4 lightPos1 = vec4(1.0, 0.0, 0.0, 0.0);
  // vec3 lightDir1 = vec3(viewMatrix * lightPos1);
  // lightDir1 = normalize(lightDir1);

  // // Defining second light
  // vec4 lightPos2 = vec4(0.0, 0.0, 1.0, 0.0);
  // vec3 lightDir2 = vec3(viewMatrix * lightPos2);
  // lightDir2 = normalize(lightDir2);

  // vec4 spotlightPos = vec4(0.0, 1.0, 0.0, 1.0);
  // vec3 spotlightDir = vec3(viewMatrix * spotlightPos);
  // spotlightDir = normalize(spotlightDir);

  // gl_Position = uModelViewMatrix * vPosition;

  // vec3 n = normalize(normalMatrix * normalize(vNormal));
  // float dotProduct = dot(n, lightDir1);
  // float intensity =  max( dotProduct, 0.0);

  // Compute specular component only if light falls on vertex
  // if(intensity > 0.0)
  // {
  //   vec3 eye = normalize( vec3(-gl_Position));
  //   vec3 h = normalize(lightDir1 + eye );
  //   float intSpec = max(dot(h,n), 0.0);
  //       spec = specular * pow(intSpec, shininess);
  // }

  // color = max((intensity * diffuse  + spec)*vColor, ambient); // All

  // dotProduct = dot(n, lightDir2);
  // intensity =  max( dotProduct, 0.0);

  // // Compute specular component only if light falls on vertex
  // if(intensity > 0.0)
  // {
  //   vec3 eye = normalize( vec3(-gl_Position));
  //   vec3 h = normalize(lightDir2 + eye );
  //   float intSpec = max(dot(h,n), 0.0);
  //       spec = specular * pow(intSpec, shininess);
  // }

  // color += max((intensity * diffuse  + spec)*vColor, ambient);

  // vec3 dir = gl

  // dotProduct = dot(n, spotlightPos);
  // intensity =  max( dotProduct, 0.0);

  // // Compute specular component only if light falls on vertex
  // if(intensity > 0.0)
  // {
  //   vec3 eye = normalize( vec3(-gl_Position));
  //   vec3 h = normalize(spotlightDir + eye );
  //   float intSpec = max(dot(h,n), 0.0);
  //       spec = specular * pow(intSpec, shininess);
  // }

  // color += max((intensity * diffuse  + spec)*vColor, ambient);

// }
    ecPos = uModelViewMatrix * vPosition;
    gl_Position = uModelViewMatrix * vPosition;
    normal = (normalMatrix * normalize(vNormal));
    eye = - (uModelViewMatrix * gl_Position);
    COLOR = vColor;
    s1 = switch1;
    s2 = switch2;
    s3 = switch3;
 }
