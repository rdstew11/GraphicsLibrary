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

static void frameResizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

static void GLAPIENTRY debugCallback( GLenum source,
                                      GLenum type,
                                      GLuint id,
                                      GLenum severity,
                                      GLsizei length,
                                      const GLchar* message,
                                      const void* userParam ) {
    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
             ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), type, severity, message );
}

GLFWwindow* initializeWindow(){
    if (!glfwInit()){
        printf("Failed to initialize GLFW.");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

    int width = 640, height = 480;
    const char* window_title = "Window";

    GLFWwindow* window = glfwCreateWindow(640, 480, window_title, NULL, NULL);

    if (!window){
        printf("Window broke");
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    // Glad Loads OpenGL into GLFW process
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        printf("Failed to initialize GLAD");
        exit(EXIT_FAILURE);
    };

    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( debugCallback, 0 );
    glFrontFace(GL_CW);
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, frameResizeCallback);

    return window;
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

void activateProgram(ShaderProgram program){
    glUseProgram(program.id);
}

ShaderProgram initShaderProgram(const char* vert_shader_path, const char* frag_shader_path){
    ShaderProgram program;
    program.id = glCreateProgram();

    GLuint vertShader = initShader(GL_VERTEX_SHADER, vert_shader_path);
    GLuint fragShader = initShader(GL_FRAGMENT_SHADER, frag_shader_path);

    glAttachShader(program.id, fragShader);
    glAttachShader(program.id, vertShader);
    glLinkProgram(program.id);

    glDeleteShader(fragShader);
    glDeleteShader(vertShader);

    checkProgramInitStatus(program);

    return program;
}

void setUniformMatrix4fv(ShaderProgram program, const char* name, float* value){
    activateProgram(program);
    int location = glGetUniformLocation(program.id, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, value);
}
