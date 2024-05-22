#include <stdio.h>
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

int main() {
    GLFWwindow* window = glfwCreateWindow(640, 480, "Window", NULL, NULL);

    if (!window){
        printf("Window broke");
    }

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
}
