#include "model.h"

#include <vector>

model::Model model::load(const std::string &path)
{
    std::vector<vertex> vertices;
    vertices.emplace_back(vertex{glm::vec4{0.0f, 0.0f, 0.0f, 1.0f}});
    vertices.emplace_back(vertex{glm::vec4{1.0f, 2.0f, 0.0f, 1.0f}});
    vertices.emplace_back(vertex{glm::vec4{20.0f, 10.0f, 0.0f, 1.0f}});
    const std::vector<GLuint> indices{0, 1, 2};

    return model::Model{hardware_buffer(vertices, indices)};
}