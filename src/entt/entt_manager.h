#include <../vendor/entt.h>

class entt_manager
{
public:
    static void init();
    static void update(entt::registry &registry);
};
