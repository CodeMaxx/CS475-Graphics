#version 330

in vec3 normal;
in vec4 eye;
in vec4 COLOR;
in vec2 tex;
uniform int nodeNum;

uniform mat4 viewMatrix;
uniform sampler2D texture;

out vec4 frag_color;

in float s1;
in float s2;

void main ()
{
    // Defining Materials
    vec4 diffuse = vec4(0.5, 0.0, 0.0, 1.0);
    vec4 ambient = vec4(0.1, 0.0, 0.0, 1.0);
    vec4 specular = vec4(1.0, 0.5, 0.5, 1.0);
    float shininess = 10.0;
    vec4 spec = vec4(0.0);

    // Defining Light
    vec4 lightPos1 = vec4(1.0, 1.0, 1.0, 0.0);
    vec3 lightDir1 = vec3(viewMatrix * lightPos1);
    lightDir1 = normalize(lightDir1);

    // Defining second light
    vec4 lightPos2 = vec4(-1.0, 1.0, 1.0, 0.0);
    vec3 lightDir2 = vec3(viewMatrix * lightPos2);
    lightDir2 = normalize(lightDir2);

    vec4 color = vec4(0.0);

    vec3 n = normalize(vec3(normal));

    if(s1 > 0.5) {
        //Diffuse
        float dotProduct = dot(n, lightDir1);
        float intensity =  max( dotProduct, 0.0);

        // Compute specular component only if light falls on vertex

        if(intensity > 0.0)
        {
        vec3 e = normalize(vec3(eye));
        vec3 h = normalize(lightDir1 + e );
        float intSpec = max(dot(h,n), 0.0);
        spec = specular * pow(intSpec, shininess);
        }

        color += max((intensity * diffuse  + spec)*COLOR, ambient); // All
    }

    if(s2 > 0.5) {
        // Adding Second light component
        float dotProduct = dot(n, lightDir2);
        float intensity =  max( dotProduct, 0.0);

        if(intensity > 0.0)
        {
        vec3 e = normalize(vec3(eye));
        vec3 h = normalize(lightDir1 + e );
        float intSpec = max(dot(h,n), 0.0);
        spec = specular * pow(intSpec, shininess);
        }

        color += max((intensity * diffuse  + spec)*COLOR, ambient);
    }

    //vec4 color = intensity * diffuse; // Only Diffuse
    //frag_color = color;

    //if(nodeNum == 0) {
    	frag_color = texture2D(texture, tex);
    //}
}
