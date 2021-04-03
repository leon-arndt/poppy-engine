#include "renderer.h"
#include "mesh_renderer.h"

namespace renderer
{
    void render(const entt::registry* registry)
    {
        mesh_renderer::render(registry);
    }
}
