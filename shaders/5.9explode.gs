#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
vec2 texCoords;
vec3 position;
} gs_in[];

out vec2 TexCoords;

uniform float time;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


vec3 explode(vec3 position, vec3 normal)
{
    float magnitude = 2.0;
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude; 
    return position + direction;
}

vec3 GetNormal()
{
    vec3 pos0 = vec3(gs_in[0].position);
    vec3 pos1 = vec3(gs_in[1].position);
    vec3 pos2 = vec3(gs_in[2].position);

    vec3 a = pos2 - pos1;
    vec3 b = pos0 - pos1;
    return normalize(cross(a, b));
}

void main() {    
    mat4 mvp = projection * view * model;
    vec3 normal = GetNormal();

    vec3 pos = gs_in[0].position;
    gl_Position = mvp * vec4(explode(pos, normal),1.0);
    TexCoords = gs_in[0].texCoords;
    EmitVertex();

    pos = gs_in[1].position;
    gl_Position = mvp * vec4(explode(pos, normal),1.0);
    TexCoords = gs_in[1].texCoords;
    EmitVertex();

    pos = gs_in[2].position;
    gl_Position = mvp * vec4(explode(pos, normal),1.0);
    TexCoords = gs_in[1].texCoords;
    EmitVertex();

    EndPrimitive();
}