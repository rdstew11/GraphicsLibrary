#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

int main() {
    printf("Hello");
    if (!glfwInit()){
        printf("Failed to initialize GLFW.");
        exit(EXIT_FAILURE);
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Window", NULL, NULL);

    if (!window){
        printf("Window broke");
    }

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    Sleep(10000);

    printf("complete");
}
