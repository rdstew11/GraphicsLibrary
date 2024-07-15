#include "shaderprogram.h"
#include <stdio.h>
#include <malloc.h>

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
    char * buffer = 0;
    long length;
    FILE * fin = fopen(path, "rb");

    if (fin) {
        fseek(fin, 0, SEEK_END);
        length = ftell(fin) + 1;
        fseek(fin, 0, SEEK_SET);
        buffer = malloc(length);

        if(buffer) {
            fread(buffer, 1, length, fin);
            buffer[length] = '\0';
        }
        fclose(fin);
    }

    if(buffer){
        return buffer;
    } else {
        printf("Failed to read from: %s\n", path);
        exit(1);
    }
}

GLuint initShader(GLenum type, const char* path){
    const char* source = readFile(path);

    printf("Path: %s, Contents:\n%s\n", path, source);

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    checkShaderCompileStatus(shader);
    return shader;
}

void checkProgramInitStatus(GLuint program){
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if(!success){
        glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
        printf("%s", infoLog);
    }
}

void printProgramLog(GLuint program){
    char infoLog[512];
    glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
    printf("%s", infoLog);
}
