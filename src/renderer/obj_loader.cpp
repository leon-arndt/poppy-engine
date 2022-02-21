#include "obj_loader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtx/norm.hpp>

namespace obj_loader
{

    struct face
    {
        std::vector<GLuint> pos;
    };

    void tessellate_faces(std::vector<face> faces, tmp_buffer_data &data)
    {
        assert(data.vertex_indices.size() == 0);
        for (const auto &fc : faces)
        {
            size_t size = fc.pos.size();
            if (size > 3)
            {
                glm::vec4 avg_pos(0.0f, 0.0f, 0.0f, 0.0f);
                glm::vec2 avg_tex{0.0f, 0.0f};
                glm::vec3 avg_norm{0.0f, 0.0f, 0.0f};

                //Add average of all vertices of the face to use as the center for a triangle fan
                for (size_t i = 0; i < size; ++i)
                {
                    avg_pos += data.vertices[fc.pos[i]];
                    avg_tex += data.tex_coords[fc.pos[i]];
                    avg_norm += data.normals[fc.pos[i]];
                }

                avg_pos /= size;
                avg_tex /= size;
                avg_norm /= size;

                data.vertices.emplace_back(avg_pos);
                data.tex_coords.emplace_back(avg_tex);
                data.normals.emplace_back(avg_norm);

                //Index of the new average vertex
                GLuint pos_index = data.vertices.size() - 1;
                GLuint tex_index = data.tex_coords.size() - 1;
                GLuint norm_index = data.normals.size() - 1;

                for (size_t i = 1; i <= size; ++i)
                {
                    data.vertex_indices.emplace_back(pos_index);
                    data.vertex_indices.emplace_back(fc.pos[(i - 1) % size]);
                    data.vertex_indices.emplace_back(fc.pos[i % size]);
                }
            }
            else
            {
                for (size_t i = 0; i < 3; ++i)
                {
                    size_t index = std::min(size - 1, i);
                    data.vertex_indices.emplace_back(fc.pos[index]);
                }
            }
        }
    }

    tmp_buffer_data load(const std::string &path, bool normalize)
    {
        tmp_buffer_data data;
        std::vector<face> faces;
        data.clear();

        // Biggest indices for each array to ensure there are no dangling indices
        GLuint pos_index_max = 0;
        std::vector<GLuint> pos_indices, norm_indices, tex_indices;
        std::vector<glm::vec3> norm_unordered;
        std::vector<glm::vec2> tex_unordered;

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
                    data.vertices.emplace_back(vertex(x, y, z, 1.0f));
                }

                else if (type == "vt")
                {
                    float u, v, w;
                    iss >> u >> v >> w;
                    tex_unordered.emplace_back(glm::vec2{u, v});
                }

                else if (type == "vn")
                {
                    float x, y, z;
                    iss >> x >> y >> z;
                    norm_unordered.emplace_back(glm::vec3{x, y, z});
                }
                else if (type == "f")
                {
                    faces.emplace_back();
                    face &fc = faces.back();
                    while (iss)
                    {
                        std::string subline;
                        iss >> subline;
                        std::istringstream sub_iss(subline);

                        std::string vdata;
                        if (sub_iss && std::getline(sub_iss, vdata, '/'))
                        {
                            if (vdata.size() > 0)
                            {
                                int index = std::stoi(vdata);
                                const GLuint pos_index = GLuint((index >= 0) ? index - 1 : data.vertices.size() + index);
                                pos_index_max = std::max(pos_index_max, pos_index);
                                fc.pos.emplace_back(pos_index);
                                pos_indices.emplace_back(pos_index);
                            }
                        }
                        if (sub_iss && std::getline(sub_iss, vdata, '/'))
                        {
                            if (vdata.size() > 0)
                            {
                                int index = std::stoi(vdata);
                                const GLuint tex_index = GLuint((index >= 0) ? index - 1 : data.vertices.size() + index);
                                tex_indices.emplace_back(tex_index);
                            }
                        }
                        if (sub_iss && std::getline(sub_iss, vdata, '/'))
                        {
                            if (vdata.size() > 0)
                            {
                                int index = std::stoi(vdata);
                                const GLuint norm_index = GLuint((index >= 0) ? index - 1 : data.vertices.size() + index);
                                norm_indices.emplace_back(norm_index);
                            }
                        }
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
            return data;
        }

        data.vertices.resize(pos_index_max + 1);
        data.tex_coords.resize(pos_index_max + 1);
        data.normals.resize(norm_unordered.size());

        std::cout << pos_indices.size() << " " << norm_indices.size() << std::endl;
        for (size_t i = 0; i < norm_indices.size(); ++i)
        {
            data.normals[pos_indices[i]] = norm_unordered[norm_indices[i]];
        }

        std::cout << " GGGGGGG3 << std::endl" << std::endl;

        if (normalize)
        {
            float max_excentric = std::numeric_limits<float>::min();
            for (const auto &v : data.vertices)
            {
                max_excentric = std::max(max_excentric, v.x);
                max_excentric = std::max(max_excentric, v.y);
            }

            float norm_factor = 1.0f / max_excentric;

            for (size_t i = 0; i < data.vertices.size(); ++i)
            {
                data.vertices[i] *= norm_factor;
            }
        }

        tessellate_faces(faces, data);

        std::cout << "done loading model" << std::endl;
        return data;
    }

}