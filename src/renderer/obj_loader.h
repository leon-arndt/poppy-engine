#pragma once

#include <string>

#include "model.h"

namespace obj_loader
{
    model::Model load(std::string path);
}