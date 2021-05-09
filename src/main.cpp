#define GLFW_INCLUDE_NONE

#include <iostream>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include "../vendor/entt.h"
#include "../glad/glad.h"
#include "util/error.h"
#include "entt/entt_manager.h"
#include "editor/editor.h"
#include "renderer/renderer.h"

int main(int argc, char *argv[])
{
    if (!glfwInit())
    {
        std::cerr << "Initialization failed" << std::endl;
    }

    entt_manager::init();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    auto window = glfwCreateWindow(640, 480, "Poppy Engine", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetWindowCloseCallback(window, [](GLFWwindow *window) { glfwSetWindowShouldClose(window, 1); });
    if (!gladLoadGL())
    {
        std::cerr << "Failed to initialize GL" << std::endl;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(error::openglCallbackFunction, nullptr);
    GLuint unusedIds = 0;
    glDebugMessageControl(GL_DONT_CARE,
                          GL_DONT_CARE,
                          GL_DONT_CARE,
                          0,
                          &unusedIds,
                          true);

    editor::init();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    editor::init2(window);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // feed inputs to dear imgui, start new frame
        editor::clear();

        //draw geometry here
        renderer::render(entt_manager::get_registry());
        editor::scaffold();
        editor::render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glfwSwapBuffers(window);
    }

    //clean up
    editor::destroy();
    glfwDestroyWindow(window);

    return 0;
}
