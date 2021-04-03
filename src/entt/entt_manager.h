#include <../vendor/entt.h>
#include <memory>

class entt_manager
{
public:
    static void init();
    static void update(entt::registry* registry);
    static entt::registry* get_registry() {return registry;}
    
    static entt::registry* registry;
};
