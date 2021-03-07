#define GLFW_INCLUDE_NONE

#include <iostream>
#include <GLFW/glfw3.h>
#include <unistd.h>

#include "../vendor/entt.h"
#include "transform.h"
#include "../glad/glad.h"

#include "renderer/model.h"
#include "renderer/resource_manager.h"
#include "util/error.h"

int main(int argc, char *argv[])
{
    if (!glfwInit())
    {
        std::cerr << "Initialization failed" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    auto window = glfwCreateWindow(320, 240, "test", nullptr, nullptr);
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

    entt::registry registry;

    render_resource_manager res;
    res.load_shader("forward", "../resources/shader/forward.vert", "../resources/shader/forward.frag");

    model::Model mdl = model::load("bla");

    const auto shader = res.get_shader("forward");

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glUseProgram(shader);

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(mdl.vao.vao);
        glDrawElements(GL_TRIANGLES, mdl.vao.size, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();

        //Transform transform;
    }

    glfwTerminate();
}