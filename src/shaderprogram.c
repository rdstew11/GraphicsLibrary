#include "shaderprogram.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>

static const char* readFile(const char* path){
    char * buffer = 0;
    char* newBuffer = NULL;
    long length;
    FILE * fin = fopen(path, "r");

    if (fin) {
        fseek(fin, 0, SEEK_END);
        length = ftell(fin);
        fseek(fin, 0, SEEK_SET);
        buffer = malloc(sizeof(char) * length);

        if(buffer) {
            const size_t fileLength = fread(buffer, 1, length, fin);
            newBuffer = realloc(buffer, fileLength + 1);
            newBuffer[fileLength] = '\0';
        }
        fclose(fin);
    }

    if(newBuffer){
        return newBuffer;
    } else {
        printf("Failed to read from: %s\n", path);
        exit(1);
    }
}

static void checkShaderCompileStatus(GLuint shader){
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        printf("%s", infoLog);
        exit(1);
    }
}

static GLuint initShader(GLenum type, const char* path){
    const char* source = readFile(path);

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    free((void * )source);
    source = NULL;

    checkShaderCompileStatus(shader);
    return shader;
}

static void checkProgramInitStatus(ShaderProgram program){
    int success;
    char infoLog[512];
    glGetProgramiv(program.id, GL_LINK_STATUS, &success);

    if(!success){
        glGetProgramInfoLog(program.id, sizeof(infoLog), NULL, infoLog);
        printf("%s", infoLog);
        exit(1);
    }
}

void printProgramLog(ShaderProgram program){
    char infoLog[512];
    glGetProgramInfoLog(program.id, sizeof(infoLog), NULL, infoLog);
    printf("%s", infoLog);
}



ShaderProgram initShaderProgram(const char* vertShaderPath, const char* fragShaderPath){
    ShaderProgram program;
    program.id = glCreateProgram();

    GLuint vertShader = initShader(GL_VERTEX_SHADER, vertShaderPath);
    GLuint fragShader = initShader(GL_FRAGMENT_SHADER, fragShaderPath);

    glAttachShader(program.id, fragShader);
    glAttachShader(program.id, vertShader);
    glLinkProgram(program.id);

    glDeleteShader(fragShader);
    glDeleteShader(vertShader);

    glFrontFace(GL_CW);

    checkProgramInitStatus(program);

    return program;
}
