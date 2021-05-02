#pragma once

#include <glm/vec4.hpp>
#include <string>

typedef glm::vec4 vertex;

auto dump_vtx = [](vertex v) { return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ")"; };