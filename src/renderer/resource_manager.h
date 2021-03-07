#pragma once

#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include "glm/vec4.hpp"
#include <vector>
#include <unordered_map>
#include <string>

class render_resource_manager
{
    std::unordered_map<std::string, GLuint> shaders;

public:
    bool load_shader(const std::string &name, const std::string &vertex_path, const std::string &fragment_path);
    GLuint get_shader(const std::string &name);
};