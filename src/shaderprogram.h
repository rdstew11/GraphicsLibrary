#ifndef GRAPHICSLIBRARY_SHADERPROGRAM_H
#define GRAPHICSLIBRARY_SHADERPROGRAM_H

#endif

#include "glad/glad.h"

struct ShaderProgram{
    GLuint program;
};

void initShaderProgram();

GLuint initShader();
