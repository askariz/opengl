//
// Created by askariz on 11/16/18.
//

#include <GLFW/glfw3.h>

int main(void){
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glViewport(0,0,800,600);
    while(1){
        //glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 1;
}