#define GLFW_INCLUDE_NONE

#include <iostream>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "../vendor/entt.h"
#include "../glad/glad.h"
#include "util/error.h"
#include "entt/entt_manager.h"
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
    auto window = glfwCreateWindow(320, 240, "glfw Window", nullptr, nullptr);
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::GetIO().Fonts->AddFontDefault();
    ImGui::GetIO().Fonts->Build();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ImVec2 vec;
    vec.x = 160;
    vec.y = 90;
    io.DisplaySize = vec;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        //draw geometry here
        renderer::render(entt_manager::get_registry());

        // render your GUI
        ImGui::Begin("imGUi window");
        ImGui::Button("Hello Lukas!");
        ImGui::End();

        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glfwSwapBuffers(window);
    }

    //clean up
    ImGui::DestroyContext();
    glfwDestroyWindow(window);

    return 0;
}
