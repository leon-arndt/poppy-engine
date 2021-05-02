#pragma once

#include <string>
#include <vector>
#include <GL/gl.h>

#include "types.h"
#include "hardware_resources.h"

namespace obj_loader
{
    tmp_buffer_data load(const std::string &path, bool normalize = false);
}