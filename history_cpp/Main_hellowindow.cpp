#include "Main.h"
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//模式
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//mac
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //设置窗口尺寸
    framebuffer_size_callback(window, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//注册函数每当窗口调整大小的时候调用这个函数

    //渲染循环
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);//交换颜色缓冲
        glfwPollEvents();//检查触发事件
    }

    glfwTerminate();
    return 0;
}

