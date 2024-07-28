#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cglm/mat4.h>
#include <cglm/affine.h>
#include <cglm/util.h>

#include "shaderprogram.h"
#include "object.h"



static void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
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

    GLFWwindow* window = initializeWindow();

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

    ShaderProgram program = initShaderProgram(vertSourcePath, fragSourcePath);
    Object* catTriangle = malloc(sizeof (Object));
    initializeObject(catTriangle, vertices, sizeof(vertices),indices, sizeof(indices), 6);
    loadObjectTexture(catTriangle, texturePath);

    // Initialize Matrix Math inputs
    mat4 translationMatrix = GLM_MAT4_IDENTITY_INIT;
    vec3 translateVector = {0.25f, 0.25f, 0.0f};
    vec3 scaleVector = {0.5f, 0.5f, 0.5f};

    glm_translate_make(translationMatrix, translateVector);

    glm_rotate_z(translationMatrix, glm_rad(130.0f), translationMatrix);
    glm_scale(translationMatrix, scaleVector);



    setUniformMatrix4fv(program, "transform", translationMatrix[0]);

    // Triangle Face Directions
    time_t startTime, currentTime;
    time ( &startTime );
    currentTime = startTime;
    float angle = 0.0f;


    while (!glfwWindowShouldClose((window))){
        activateProgram(program);
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        mat4 newTranslationMatrix = GLM_MAT4_IDENTITY_INIT;

        glm_translate_make(newTranslationMatrix, translateVector);

        glm_rotate_z(newTranslationMatrix, glm_rad(angle), newTranslationMatrix);
        glm_scale(newTranslationMatrix, scaleVector);
        setUniformMatrix4fv(program, "transform", newTranslationMatrix[0]);

        drawObject(catTriangle);

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


