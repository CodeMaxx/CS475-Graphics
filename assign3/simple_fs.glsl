#version 330

in vec3 normal;
in vec4 eye;
in vec4 COLOR;
in vec2 tex;

uniform mat4 viewMatrix;
in vec4 ecPos;
uniform sampler2D texture1;

out vec4 frag_color;

in float s1;
in float s2;
in float s3;

void main () {
    // Defining Materials
    vec4 diffuse = vec4(0.35, 0.35, 0.35, 1.0);
    vec4 ambient = vec4(0.2, 0.2, 0.2, 1.0);
    vec4 specular = vec4(0.25, 0.25, 0.25, 1.0);
    float shininess = 1.0;
    vec4 spec = vec4(0.5);

    vec4 texImage = texture(texture1, tex);

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

        if(intensity > 0.0) {
            vec3 e = normalize(vec3(eye));
            vec3 h = normalize(lightDir1 + e );
            float intSpec = max(dot(h,n), 0.0);
            spec = specular * pow(intSpec, shininess);
        }

        color += (intensity * diffuse  + spec)*texImage; // All
    }

    if(s2 > 0.5) {
        // Adding Second light component
        float dotProduct = dot(n, lightDir2);
        float intensity =  max( dotProduct, 0.0);

        if(intensity > 0.0) {
            vec3 e = normalize(vec3(eye));
            vec3 h = normalize(lightDir2 + e );
            float intSpec = max(dot(h,n), 0.0);
            spec = specular * pow(intSpec, shininess);
        }

        color += (intensity * diffuse  + spec)*texImage;
    }

    if(s3 > 0.5) {
        vec4 spotlightPos = vec4(0.0, 2.0, 0.0, 1.0);
        vec3 spotlightDir = vec3(spotlightPos - ecPos);
        float dist = length(spotlightDir);
        float dotProduct = dot(n,normalize(spotlightDir));
        float intensity =  max( dotProduct, 0.0);

        vec3 spotDirection = vec3(0.0, -1.0, 0.3); // Axis of the cone

        if(intensity > 0.2) {
            vec3 e = normalize(vec3(eye));
            vec3 h = normalize(spotlightDir + e );
            float spotEffect = dot(normalize(spotDirection), normalize(-spotlightDir));
            if(spotEffect > 0.96) {
                color += spotEffect * (diffuse * intensity + ambient) * texImage;
                float intSpec = max(dot(h,n), 0.0);
                spec = specular * pow(intSpec, shininess);
                color += spotEffect * spec * texImage;
            }
        }
    }

     if(s1 > 0.5 || s2 > 0.5)
         color = max(color, ambient);

    //vec4 color = intensity * diffuse; // Only Diffuse
    frag_color = color;

}
