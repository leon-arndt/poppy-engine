#define GLFW_INCLUDE_NONE

#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include "../vendor/entt.h"

int main(int argc, char* argv[]){
    if(!glfwInit()){
        std::cerr << "Initialization failed" << std::endl;
    }

    auto window = glfwCreateWindow(320, 240, "test", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    entt::registry registry;

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
 
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        Transform transform;
    }

    sleep(5);

    glfwTerminate();
}