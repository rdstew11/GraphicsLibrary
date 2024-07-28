#ifndef GRAPHICSLIBRARY_OBJECT_H
#define GRAPHICSLIBRARY_OBJECT_H
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define OBJECT_DRAW_TYPE GL_UNSIGNED_INT
#define OBJECT_DRAW_MODE GL_TRIANGLES

typedef struct {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint texture;
    int count;
} Object;

void initializeObject(Object* object, float* vertices, GLsizeiptr vertexSize, int* indices, GLsizeiptr indexSize, int count);
void loadObjectTexture(Object* object, const char* image_path);
void drawObject(Object* object);

