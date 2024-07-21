#ifndef GRAPHICSLIBRARY_SHADERPROGRAM_H
#define GRAPHICSLIBRARY_SHADERPROGRAM_H

#endif

#include "glad/glad.h"

typedef struct {} Uniform;

typedef struct{
    GLuint id;
} ShaderProgram;


ShaderProgram initShaderProgram(const char* vertShaderPath, const char* fragShaderPath);
void printProgramLog(ShaderProgram program);