#include "resource_manager.h"

#include <GL/gl.h>
#include <fstream>
#include <sstream>
#include <iostream>

bool render_resource_manager::load_shader(const std::string &name, const std::string &vertex_path, const std::string &fragment_path)
{
    try
    {
        std::ifstream vert_in(vertex_path);
        std::ifstream frag_in(fragment_path);

        if (!vert_in)
        {
            std::cerr << "Shader not found: " << vertex_path << std::endl;
        }

        if (!frag_in)
        {
            std::cerr << "Shader not found: " << fragment_path << std::endl;
        }

        std::stringstream vertex_stream, fragment_stream;
        vertex_stream << vert_in.rdbuf();
        fragment_stream << frag_in.rdbuf();

        std::string vertex_source = vertex_stream.str();
        std::string fragment_source = fragment_stream.str();

        auto vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        const auto vertex_source_bytes = vertex_source.data();
        glShaderSource(vertex_shader, 1, &vertex_source_bytes, nullptr);
        glCompileShader(vertex_shader);

        auto fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        const auto fragment_source_bytes = fragment_source.data();
        glShaderSource(fragment_shader, 1, &fragment_source_bytes, nullptr);
        glCompileShader(fragment_shader);

        auto check_compilation_errors = [&](GLuint shader) {
            GLint success = GL_FALSE;
            glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
            if (success != GL_TRUE)
            {
                GLint max_length = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

                std::vector<GLchar> log(max_length);
                glGetShaderInfoLog(shader, max_length, &max_length, log.data());

                std::cout << std::string(log.begin(), log.end()) << std::endl;

                return false;
            }
            return true;
        };

        check_compilation_errors(vertex_shader);
        check_compilation_errors(fragment_shader);

        auto program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        shaders[name] = program;

        return true;
    }
    catch (...)
    {
        std::cerr << "Encountered exception while loading shaders" << std::endl;
    }

    return false;
}

GLuint render_resource_manager::get_shader(const std::string &name)
{
    return shaders[name];
}