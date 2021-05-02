#include "obj_loader.h"

#include <fstream>
#include <sstream>
#include <iostream>

model::Model load(std::string path)
{
    std::vector<vertex> vertices;
    std::vector<GLuint> indices;

    try
    {
        auto in = std::ifstream(path);

        std::string line;
        while (std::getline(in, line))
        {
            std::istringstream iss(line);

            std::string type;
            iss >> type;

            if (type == "v")
            {
                float x, y, z;
                iss >> x >> y >> z;
                vertices.emplace_back(vertex{glm::vec4{x, y, z, 1.0f}});
            }

            else if (type == "vt")
            {
                //TODO
            }

            else if (type == "vn")
            {
                //TODO
            }

            else if (type == "f")
            {
                while (iss)
                {
                    GLuint index;
                    iss >> index;
                    indices.emplace_back(index);
                }
            }

            else if (type == "g")
            {
                //TODO
            }

            else if (type == "usemtl")
            {
                //TODO
            }
        }
    }
    catch (...)
    {
        std::cerr << "Failed to load model " << path << std::endl;
    }

    return model::Model(vertices, indices);
}