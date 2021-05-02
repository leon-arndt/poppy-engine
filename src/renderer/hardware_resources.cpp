#include "hardware_resources.h"

#include <iostream>

hardware_buffer::hardware_buffer(const tmp_buffer_data &data)
{
    GLuint vbo, ibo, nvbo, nibo, tvbo, tibo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // upload vertex buffers
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.vertices.size() * sizeof(vertex), data.vertices.data(), GL_STATIC_DRAW);

    // pos attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.vertex_indices.size() * sizeof(GLuint), data.vertex_indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // upload normal buffers
    glGenBuffers(1, &nvbo);
    glBindBuffer(GL_ARRAY_BUFFER, nvbo);
    glBufferData(GL_ARRAY_BUFFER, data.normals.size() * sizeof(glm::vec3), data.normals.data(), GL_STATIC_DRAW);

    // normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

    // upload texcoord buffers
    glGenBuffers(1, &tvbo);
    glBindBuffer(GL_ARRAY_BUFFER, tvbo);
    glBufferData(GL_ARRAY_BUFFER, data.tex_coords.size() * sizeof(glm::vec2), data.tex_coords.data(), GL_STATIC_DRAW);

    // texcoord attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &nvbo);

    size = data.vertex_indices.size();
}

hardware_buffer::~hardware_buffer()
{
    //TODO: Release hardware memory
}