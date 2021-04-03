#include "mesh_renderer.h"
#include <iostream>
#include "entt/components/comp_mesh_render.h"

namespace mesh_renderer
{
    void render(const entt::registry* registry)
    {
        auto view = registry->view<const MeshRenderComponent>();
        view.each([](const auto &comp) {
            /* ... */
            std::cout << "mesh renderer: " << std::endl;
        });
    }
}
