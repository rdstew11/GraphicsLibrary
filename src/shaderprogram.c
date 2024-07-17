#include "shaderprogram.h"
#include <stdio.h>
#include <string.h>
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
    char* newBuffer = NULL;
    long length;
    FILE * fin = fopen(path, "rb");

    if (fin) {
        fseek(fin, 0, SEEK_END);
        length = ftell(fin);
        fseek(fin, 0, SEEK_SET);
        buffer = malloc(sizeof(char) * length);

        if(buffer) {
            int c;
            int counter = 0;
            while((c = fgetc(fin)) != EOF){
                if (c != '\r'){
                    buffer[counter] = (char) c;
                    counter++;
                }
            }
            newBuffer = realloc(buffer, counter);
            newBuffer[counter] = '\0';
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

GLuint initShader(GLenum type, const char* path){
    const char* source = readFile(path);

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    free((void * )source);
    source = NULL;

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
