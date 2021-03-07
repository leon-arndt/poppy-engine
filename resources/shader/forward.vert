#version 330
layout(location = 0) in vec4 pos;

out vec3 color;

void main(){
    gl_Position = pos;
    color = vec3(1.0, 1.0, 0.0);
}