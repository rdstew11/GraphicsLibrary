#ifndef GRAPHICSLIBRARY_SHADERPROGRAM_H
#define GRAPHICSLIBRARY_SHADERPROGRAM_H

#endif

#include "glad/glad.h"

typedef struct {} Uniform;

typedef struct{
    GLuint program;
} ShaderProgram;

ShaderProgram initShaderProgram();

GLuint initShader(GLenum type, const char* path);
void checkProgramInitStatus(GLuint program);
void printProgramLog(GLuint program);