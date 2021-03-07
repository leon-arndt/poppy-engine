#define GLFW_INCLUDE_NONE
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include "../vendor/entt.h"
#include "../vendor/imgui-1.79/imgui.h"
#include "../vendor/imgui-1.79/examples/imgui_impl_opengl3.h"
#include "../vendor/imgui-1.79/examples/imgui_impl_glfw.h"

struct position {
    float x;
    float y;
};

struct velocity {
    float dx;
    float dy;
};

ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

void update(entt::registry &registry) {
    printf("Update entt registry");
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

int main(int argc, char* argv[]){
    if(!glfwInit()){
        std::cerr << "Initialization failed" << std::endl;
    }

    auto window = glfwCreateWindow(320, 240, "glfw/imGui Test", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    entt::registry registry;

    //ImGui_ImplGlfw_InitForOpenGL(window, true);
    // ImGui_ImplOpenGL3_Init(glsl_version);

    //state
    bool my_tool_active = true;
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        /*
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
         */
        ImGui::NewFrame();
        ImGui::Begin("My First ImGui Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
        ImGui::End();
        glfwSwapBuffers(window);

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGui::StyleColorsDark();
        glfwSwapBuffers(window);

        /*
        //entt registry updates
        for (int i = 0; i < 10; i++) {
            const auto entity = registry.create();
            registry.emplace<position>(entity, i * 1.f, i * 1.f);
            if(i % 2 == 0) {
                registry.emplace<velocity>(entity, i * .1f, i * .1f);
            }
            update(registry);
        }
        */
    }

    //clean up
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}