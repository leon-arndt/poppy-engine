#version 330

in vec3 color;
in vec3 frag_pos;
in vec3 frag_normal;

out vec4 FragColor;

void main(){
    vec3 light_pos = vec3(-1.0, 1.0, -1.0);

    vec3 light_dir = normalize(light_pos - frag_pos);
    
    float diffuse = max(dot(-frag_normal, light_dir), 0.0);

    FragColor = vec4(diffuse * color, 1.0) + vec4(0.1, 0.1, 0.1, 0.0);
}