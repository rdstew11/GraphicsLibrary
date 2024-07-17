#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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
         // positions       // colors
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
         0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top
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

    /**
     *  Vertex Attribute Objects (VAOs) hold vertex attribute pointers and element buffer object pointers
     *  Attribute pointers point to specific sections of the Vertex Buffer objects
     *  that contain data for the corresponding attribute.
     */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /**
     *  Vertex Buffer Objects (VBOs) are raw buffers containing vertex data
     */
    GLuint vbo1;
    glGenBuffers(1, &vbo1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /**
     *  Element Buffer Objects (EBOs) are a buffer indicating in which order to render vertices.
     */
    GLuint ebo1;
    glGenBuffers(1, &ebo1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glUseProgram(program);
    glBindVertexArray(vao);
    checkProgramInitStatus(program);

    glDrawArrays(GL_TRIANGLES, 0,3);

    printProgramLog(program);

    while (!glfwWindowShouldClose((window))){
        float timeValue = (float) glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(program, "inputColor");

        glUseProgram(program);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(vao);

        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo1);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}


