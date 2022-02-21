#pragma once
#define GLFW_INCLUDE_NONE
#define GL_GLEXT_PROTOTYPES

#include <vector>
#include <GLFW/glfw3.h>
#include "opengl.h"

#include <glm/glm.hpp>

#include "../types.h"

struct tmp_buffer_data
{
    std::vector<vertex> vertices;
    std::vector<GLuint> vertex_indices;

    std::vector<glm::vec3> normals;

    std::vector<glm::vec2> tex_coords;

    void clear()
    {
        vertices.clear();
        vertex_indices.clear();
        normals.clear();
        tex_coords.clear();
    }
};

/*******************************************************\
* Immutable hardware buffers                            *
* After initializing the data assigned to these buffers *
* can safely be deleted                                 *
\*******************************************************/
struct hardware_buffer
{
    GLuint vao;
    size_t size{0};

    hardware_buffer(const tmp_buffer_data &data);
    ~hardware_buffer();
};