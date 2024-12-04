#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_height1;
uniform sampler2D texture_reflection1;
uniform sampler2D texture_normal1;
uniform samplerCube skybox;
void main()
{    
    //
    vec4  ambient = texture(texture_reflection1, TexCoords);
    //diffuse
    vec4 diffuse = texture(texture_diffuse1, TexCoords);
    //specular
    vec4 specular = vec4(vec3(texture(texture_height1,TexCoords)),1.0);
    //reflection
    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    vec3 reflection = texture(skybox,R).rgb;
    vec4 reflectColor = vec4(vec3(texture(texture_reflection1, TexCoords)) * reflection,1.0);  // 反射颜色调整

    //
    //FragColor = texture_diffuse;
    //
    FragColor = vec4(0.0,0.0,0.0,1.0);
    FragColor =  ambient*(0.2f, 0.2f, 0.2f)+ diffuse *(0.7f, 0.7f, 0.7f)+ specular + reflectColor*2.0;  // 调整反射混合权重

    //FragColor = texture_diffuse + vec4(specular,1.0f) + vec4(reflect,1.0f);
}