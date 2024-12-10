#pragma once
#include <iostream>
#include <glad/glad.h> 
#include <glfw/glfw3.h>
#include "shader.h"
#include "stb_image.h"
#include "glm/glm/glm.hpp"
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_opengl3_loader.h"
#include "camera.h"
#include "Model.h"
#include "TextureData.h"
#include "Ui.h"
#include <map>
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1000;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH*0.5, lastY = SCR_HEIGHT*0.5;
bool firstMouse = true;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//窗口
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//键鼠操作
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);


