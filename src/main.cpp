#define GLFW_INCLUDE_NONE

#include <iostream>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    if(!glfwInit()){
        std::cerr << "Initialization failed" << std::endl;
    }

    auto window = glfwCreateWindow(640, 480, "poppy", nullptr, nullptr);
    
    sleep(10);

    glfwTerminate();
}