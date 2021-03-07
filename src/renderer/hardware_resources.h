#pragma once

#define GL_GLEXT_PROTOTYPES

#include <vector>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "../types.h"

/*******************************************************\
* Immutable hardware buffers                            *
* After initializing the data assigned to these buffers *
* can safely be deleted                                 *
\*******************************************************/
struct hardware_buffer
{
    GLuint vao;
    size_t size{0};

    hardware_buffer(const std::vector<vertex> &vertices, const std::vector<GLuint> &indices);
    ~hardware_buffer();
};