#pragma once

#include "hardware_resources.h"
#include <string>

namespace model
{

    struct Model
    {
        hardware_buffer vao;
    };

    Model load(const std::string &path);

}