#include <imgui.h>
#include "editor.h"
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

void editor::init(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    ImGui::GetIO().Fonts->AddFontDefault();
    ImGui::GetIO().Fonts->Build();

    ImVec2 vec;
    vec.x = 240;
    vec.y = 120;
    io.DisplaySize = vec;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void editor::scaffold()
{
    ImGui::Begin("Inspector");
    static float testFloat3[4] = {0.10f, 0.20f, 0.30f, 0.42f};
    ImGui::InputFloat3("translation", testFloat3);
    ImGui::InputFloat3("rotation", testFloat3);
    ImGui::InputFloat3("scale", testFloat3);
    ImGui::InputFloat3("skew", testFloat3);
    ImGui::Button("Reset Transform");
    ImGui::End();

    ImGui::Begin("Hierarchy");
    const char *listbox_items[] = {"Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon"};
    static int listbox_item_current = -1, listbox_item_current2 = -1;
    ImGui::PushItemWidth(-1);
    ImGui::ListBox("##listbox2", &listbox_item_current2, listbox_items, IM_ARRAYSIZE(listbox_items), 12);
    ImGui::PopItemWidth();
    ImGui::End();
}

void editor::clear()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void editor::render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void editor::destroy()
{
    ImGui::DestroyContext();
}
