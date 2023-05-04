#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <windows.h>
#include "functions.h"

const auto [WIDTH, HEIGHT] = GetFullSize();
GLint WindowWidth, WindowHeight;
GLfloat ClearColor[4]{0.26, 0.25, 0.27, 1};
bool FullScreen = true;
GLuint VBO;

float Triangle[]{
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

void ResizeWindow(GLFWwindow *wd, int32_t w, int32_t h);
void UserInput(GLFWwindow *wd, int32_t key, int32_t scode, int32_t action, int32_t mod);


int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    GLFWwindow* window{glfwCreateWindow(WIDTH, HEIGHT, "GL window", NULL, NULL)};
    if (!window){
        printf("Error create GLFW window!.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwGetWindowSize(window, &WindowWidth, &WindowHeight);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Error init GLAD!.");
        return -2;
    }
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);

    uint32_t vShader{GetShader("../shaders/vertex.glsl", GL_VERTEX_SHADER, 1)};
    uint32_t fShader{GetShader("../shaders/fragment.glsl", GL_FRAGMENT_SHADER, 1)};
    GLuint sProgram{LinkAndDelShaders(std::vector<uint32_t>{vShader, fShader})};

    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, ResizeWindow);
    glfwSetKeyCallback(window, UserInput);
    glClearColor(ClearColor[0], ClearColor[1], ClearColor[2], ClearColor[3]);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void ResizeWindow(GLFWwindow *wd, int32_t w, int32_t h)
{   
    std::cout<<"!";
    glfwGetWindowSize(wd, &WindowWidth, &WindowHeight);
    glViewport(0, 0, w, h);
    glfwSetWindowPos(wd, WIDTH/2-WindowWidth/2, HEIGHT/2-WindowHeight/2);
}

void UserInput(GLFWwindow *wd, int32_t key, int32_t scode, int32_t action, int32_t mod){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE){
        glfwSetWindowShouldClose(wd, true);
    }
    else if (key == GLFW_KEY_F11 && action == GLFW_RELEASE){
        glfwSetWindowSize(wd, FullScreen?WIDTH/2:WIDTH, FullScreen?HEIGHT/2:HEIGHT);
        glfwWindowHint(GLFW_DECORATED, FullScreen);
        FullScreen = !FullScreen;
    }
}
