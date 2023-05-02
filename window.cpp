#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h> 

uint16_t HEIGHT = 1000;
uint16_t WEIGHT = 1000;

void ResizeWindow(GLFWwindow* wd, int32_t w, int32_t h)
{
    glViewport(0, 0, w, h);
}


int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window{glfwCreateWindow(WEIGHT, HEIGHT, "GL window", NULL, NULL)};
    if (!window){
        printf("Error create GLFW window!.");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Error init GLAD!.");
        return -2;
    }
    glViewport(0, 0, WEIGHT, HEIGHT);
    glfwSetFramebufferSizeCallback(window, ResizeWindow);

    return 0;
}
 
