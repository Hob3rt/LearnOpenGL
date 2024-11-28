#pragma once
#include <iostream>
#include <glad/glad.h> 
#include <glfw/glfw3.h>
#include "shader.h"
#include "stb_image.h"
#include "glm/glm/glm.hpp"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "camera.h"
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH*0.5, lastY = SCR_HEIGHT*0.5;
bool firstMouse = true;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

