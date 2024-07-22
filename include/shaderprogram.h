#ifndef GRAPHICSLIBRARY_SHADERPROGRAM_H
#define GRAPHICSLIBRARY_SHADERPROGRAM_H

#endif

#include <glad/glad.h>
#include <glfw/glfw3.h>

typedef struct {} Uniform;

typedef struct{
    GLuint id;
} ShaderProgram;

GLFWwindow* initializeWindow();

ShaderProgram initShaderProgram(const char* vertShaderPath, const char* fragShaderPath);
void activateProgram(ShaderProgram program);
void printProgramLog(ShaderProgram program);

void setUniformMatrix4fv(ShaderProgram program, const char* name, float* value);