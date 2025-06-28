#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform float cutOff;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform bool spotlightEnabled;
uniform sampler2D texture1;
in vec2 TexCoords;

void main()
{

    float globalAmbientStrength = 0.15;
    vec3 globalAmbient = globalAmbientStrength * lightColor;

    vec3 lighting = globalAmbient;

if(spotlightEnabled){
    // Ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightToFrag = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightToFrag), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightToFrag, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * lightColor * 0.5;

    // Spotlight efekt
    float theta = dot(lightToFrag, normalize(-lightDir));
    float epsilon = 0.01;
    float intensity = smoothstep(cutOff - epsilon, cutOff, theta);

    lighting += (ambient + diffuse + specular) * intensity;

}

    vec3 textureColor = texture(texture1, TexCoords).rgb;
    vec3 result = lighting * objectColor * textureColor;
    FragColor = vec4(result, 1.0);

}