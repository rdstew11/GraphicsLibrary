#include "object.h"

void initObject(Object* object, float* vertices, int* indices){
    glGenVertexArrays(1, &object->vao);
    glBindVertexArray(object->vao);

    glGenBuffers(1, &object->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &object->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void drawObject(Object* object){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ebo);
    glDrawElements(object->drawMode, object->count, object->drawType, 0);
}