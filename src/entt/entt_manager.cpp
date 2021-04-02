#include "entt_manager.h"
#include <iostream>
#include <../vendor/entt.h>
#include <entt/components/comp_mesh_render.h>

struct position {
    float x;
    float y;
};

struct velocity {
    float dx;
    float dy;
};

void entt_manager::init()
{
    std::cout << "Entt Init" << std::endl;
    entt::registry registry;

    for(auto i = 0u; i < 10u; ++i) {
        const auto entity = registry.create();
        registry.emplace<position>(entity, i * 1.f, i * 1.f);
        if(i % 2 == 0) { 
            registry.emplace<velocity>(entity, i * .1f, i * .1f); 
        }
        else {
            registry.emplace<MeshRenderComponent>(entity); 
        }
    }

    update(registry);
}

void entt_manager::update(entt::registry &registry) {
    auto view = registry.view<const position, velocity>();

    // use a callback
    view.each([](const auto &pos, auto &vel) { /* ... */ });

    // use an extended callback
    view.each([](const auto entity, const auto &pos, auto &vel) { /* ... */ });

    // use a range-for
    for(auto [entity, pos, vel]: view.each()) {
        // ...
    }

    // use forward iterators and get only the components of interest
    for(auto entity: view) {
        auto &vel = view.get<velocity>(entity);
        // ...
    }
}