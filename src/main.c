#include <stdio.h>
#include <stdlib.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

static void frameResizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    if (!glfwInit()){
        printf("Failed to initialize GLFW.");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    int width = 640, height = 480;
    const char* window_title = "Window";

    GLFWwindow* window = glfwCreateWindow(640, 480, "Window", NULL, NULL);

    if (!window){
        printf("Window broke");
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    // Glad Loads OpenGL into GLFW process
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        printf("Failed to initialize GLAD");
        exit(EXIT_FAILURE);
    };

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, frameResizeCallback);

    while (!glfwWindowShouldClose((window))){
        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}


