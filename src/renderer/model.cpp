#include "model.h"

#include <vector>

#include "obj_loader.h"

model::Model model::load(const std::string &path)
{
    std::vector<vertex> vertices;
    std::vector<GLuint> indices;

    return model::Model{hardware_buffer(obj_loader::load(path, true))};
}