#ifndef GRAPHICSLIBRARY_OBJECT_H
#define GRAPHICSLIBRARY_OBJECT_H
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    int count;
    GLenum drawType;
    GLenum drawMode;



} Object;

void object_init_vao(Object* object, float* vertices, int* indices);

