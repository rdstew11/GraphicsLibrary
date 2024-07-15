#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "shaderprogram.h"


static void frameResizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

static void GLAPIENTRY debugCallback( GLenum source,
                     GLenum type,
                     GLuint id,
                     GLenum severity,
                     GLsizei length,
                     const GLchar* message,
                     const void* userParam ) {
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), type, severity, message );
}


int main() {

    const char* fragSourcePath = "src/shaders/shader1.frag";
    const char* vertSourcePath = "src/shaders/shader1.vert";

    if (!glfwInit()){
        printf("Failed to initialize GLFW.");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    int width = 640, height = 480;
    const char* window_title = "Window";

    GLFWwindow* window = glfwCreateWindow(640, 480, window_title, NULL, NULL);

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

    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( debugCallback, 0 );

    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, frameResizeCallback);


    // 2 Triangles, 1 Square
    float vertices[] =  {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };

    int indices[] = {
            0, 1, 2
    };

    GLuint vertShader = initShader(GL_VERTEX_SHADER, vertSourcePath);
    GLuint fragShader = initShader(GL_FRAGMENT_SHADER, fragSourcePath);

    GLuint program = glCreateProgram();
    glAttachShader(program, fragShader);
    glAttachShader(program, vertShader);
    glLinkProgram(program);

    glDeleteShader(fragShader);
    glDeleteShader(vertShader);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    GLuint vbo1;
    glGenBuffers(1, &vbo1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);


    glUseProgram(program);
    glBindVertexArray(vao);
    checkProgramInitStatus(program);

    printf("Drawing triangles\n");

    glDrawArrays(GL_TRIANGLES, 0,3);




    printProgramLog(program);

    while (!glfwWindowShouldClose((window))){

        glUseProgram(program);
        glBindVertexArray(vao);

        processInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0,3);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}


