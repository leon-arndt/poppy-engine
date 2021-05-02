#version 330
layout(location = 0) in vec4 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coord;

uniform mat4 mvp;

out vec3 color;
out vec3 frag_pos;
out vec3 frag_normal;

void main(){
    gl_Position = mvp * pos;
    frag_pos = vec3(gl_Position);
    frag_normal = normalize(normal);

    color = vec3(1.0, 1.0, 1.0);

}