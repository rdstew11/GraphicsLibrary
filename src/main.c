#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <cglm/vec4.h>
#include <cglm/mat4.h>
#include <cglm/affine.h>
#include <cglm/util.h>

#include "shaderprogram.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
static void matrixFun(){
    vec4 input = {1.0f, 0.0f, 0.0f, 1.0f};
    mat4 identity = GLM_MAT4_IDENTITY_INIT;
    vec4 output = {0.0f, 0.0f, 0.0f, 0.0f};

    mat4 scaleup = {{2.0f, 0.0f, 0.0f, 0.0f,},
                    {0.0f, 2.0f, 0.0f, 0.0f,},
                    {0.0f, 0.0f, 2.0f, 0.0f,},
                    {0.0f, 0.0f, 0.0f, 1.0f,}};

    vec3 translateVector = {1.0f, 1.0f, 0.0f};
    glm_translate_make(identity, translateVector);
//    glm_mat4_mulv(scaleup, input, output);

    glm_mat4_mulv(identity, input, output);


    printf("done\n");
}

static void shaderLoop(){
    const char* fragSourcePath = "src/shaders/shader1.frag";
    const char* vertSourcePath = "src/shaders/shader1.vert";
    const char* texturePath = "assets/cat.jpg";

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
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Top right
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// Bottom right
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // Bottom left
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Top Left
    };

    int indices[] = {
            0, 1, 2,
            0, 3 ,2
    };

    // Initialize Matrix Math inputs
    vec4 input = {1.0f, 0.0f, 0.0f, 1.0f};
    mat4 translationMatrix = GLM_MAT4_IDENTITY_INIT;
    vec3 translateVector = {0.25f, 0.25f, 0.0f};
    vec3 scaleVector = {0.5f, 0.5f, 0.5f};

    glm_translate_make(translationMatrix, translateVector);

    glm_rotate_z(translationMatrix, glm_rad(130.0f), translationMatrix);
    glm_scale(translationMatrix, scaleVector);

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load Texture
    int textureWidth, textureHeight, nrChannels;
    unsigned  char *data = stbi_load(texturePath, &textureWidth, &textureHeight, &nrChannels, 0);

    // Texture Attribute
    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glUseProgram(program);
    glBindVertexArray(vao);
    checkProgramInitStatus(program);

    int transformLocation = glGetUniformLocation(program, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, translationMatrix[0]);

    glFrontFace(GL_CW); // Triangle Face Directions

    glDrawArrays(GL_TRIANGLES, 0,3);

    printProgramLog(program);


    time_t startTime, currentTime;
    time ( &startTime );
    currentTime = startTime;
    float angle = 0.0f;


    while (!glfwWindowShouldClose((window))){
//        float timeValue = (float) glfwGetTime();
//        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
//        int vertexColorLocation = glGetUniformLocation(program, "inputColor");

        glUseProgram(program);
//        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);


        time ( &currentTime );
        angle = (currentTime - startTime) * 10;
//        angle = fmod(angle + (float) rawtime, 360.0f);

        mat4 newTranslationMatrix = GLM_MAT4_IDENTITY_INIT;
        vec3 newTranslateVector = {0.25f, 0.25f, 0.0f};
        vec3 scaleVector = {0.5f, 0.5f, 0.5f};

        glm_translate_make(newTranslationMatrix, newTranslateVector);

        glm_rotate_z(newTranslationMatrix, glm_rad(angle), newTranslationMatrix);
        glm_scale(newTranslationMatrix, scaleVector);
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, newTranslationMatrix[0]);


        glBindTexture(GL_TEXTURE_2D, texture1);
        glBindVertexArray(vao);

        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

int main() {
//    matrixFun();
    shaderLoop();
}


