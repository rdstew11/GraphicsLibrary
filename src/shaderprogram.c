#include "shaderprogram.h"
#include <stdio.h>

static void checkShaderCompileStatus(GLuint shader){
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        printf("%s", infoLog);
    }
}

static const char* readFile(const char* path){
    return "";
}

GLuint initShader(GLenum type, const char* path){
    const char* source = readFile(path);

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    checkShaderCompileStatus(shader);
    return shader;
}
