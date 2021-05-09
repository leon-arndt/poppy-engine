#include <examples/imgui_impl_glfw.h>

class editor
{
public:
    static void init(GLFWwindow* window);
    static void scaffold();
    static void render();
    static void clear();
    static void destroy();
};