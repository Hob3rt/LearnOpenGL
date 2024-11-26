#pragma once
#include <iostream>
#include <glad/glad.h> 
#include <glfw/glfw3.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}