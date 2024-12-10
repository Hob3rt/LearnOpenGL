#include "Main.h"
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    //Callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
        // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader asteroidShader("shaders/5.10planet_rock.vs", "shaders/5.10planet_rock.fs");
    Shader planetShader("shaders/5.10planet.vs", "shaders/5.10planet.fs");

    Shader boxesShader("shaders/box.vs", "shaders/box.fs");
    Shader lightCubeShader("shaders/light.vs", "shaders/light.fs");

    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    // positions all containers
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    // positions of the point lights
    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f,  0.2f,  2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3(0.0f,  0.0f, -3.0f)
    };
    // first, configure the cube's VAO (and VBO)
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    TextureData diffuseMap = TextureData("resource/textures/container2.png");
    TextureData specularMap = TextureData("resource/textures/container2_specular.png");
    
    // shader configuration
    // --------------------
    boxesShader.use();
    boxesShader.setInt("material.diffuse", 0);
    boxesShader.setInt("material.specular", 1);
    // load models
    // -----------
    //Model rock("resource/objects/rock/rock.obj");
    //Model planet("resource/objects/planet/planet.obj");

    // generate a large list of semi-random model transformation matrices
    // ------------------------------------------------------------------
    //unsigned int amount = 100000;
    //glm::mat4* modelMatrices;
    //modelMatrices = new glm::mat4[amount];
    //srand(static_cast<unsigned int>(glfwGetTime())); // initialize random seed
    //float radius = 150.0;
    //float offset = 25.0f;
    //for (unsigned int i = 0; i < amount; i++)
    //{
    //    glm::mat4 model = glm::mat4(1.0f);
    //    // 1. translation: displace along circle with 'radius' in range [-offset, offset]
    //    float angle = (float)i / (float)amount * 360.0f;
    //    float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
    //    float x = sin(angle) * radius + displacement;
    //    displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
    //    float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
    //    displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
    //    float z = cos(angle) * radius + displacement;
    //    model = glm::translate(model, glm::vec3(x, y, z));

    //    // 2. scale: Scale between 0.05 and 0.25f
    //    float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
    //    model = glm::scale(model, glm::vec3(scale));

    //    // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
    //    float rotAngle = static_cast<float>((rand() % 360));
    //    model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

    //    // 4. now add to list of matrices
    //    modelMatrices[i] = model;
    //}

    //// configure instanced array
    //// -------------------------
    //unsigned int buffer;
    //glGenBuffers(1, &buffer);
    //glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

    //// set transformation matrices as an instance vertex attribute (with divisor 1)
    //// note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
    //// normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
    //// -----------------------------------------------------------------------------------------------------------------------------------
    //for (unsigned int i = 0; i < rock.meshes.size(); i++)
    //{
    //    unsigned int VAO = rock.meshes[i].VAO;
    //    glBindVertexArray(VAO);
    //    // set attribute pointers for matrix (4 times vec4)
    //    glEnableVertexAttribArray(3);
    //    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    //    glEnableVertexAttribArray(4);
    //    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    //    glEnableVertexAttribArray(5);
    //    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    //    glEnableVertexAttribArray(6);
    //    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

    //    glVertexAttribDivisor(3, 1);
    //    glVertexAttribDivisor(4, 1);
    //    glVertexAttribDivisor(5, 1);
    //    glVertexAttribDivisor(6, 1);

    //    glBindVertexArray(0);
    //}

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowDemoWindow(); // Show demo window! :)
        Ui::show_window_info();
        Ui::show_camera_info(camera);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        boxesShader.use();
        boxesShader.setVec3("viewPos", camera.Position);
        boxesShader.setFloat("material.shininess", 32.0f);

        /*
           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
        */
        // directional light
        boxesShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        boxesShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        boxesShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        boxesShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        boxesShader.setVec3("pointLights[0].position", pointLightPositions[0]);
        boxesShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        boxesShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        boxesShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        boxesShader.setFloat("pointLights[0].constant", 1.0f);
        boxesShader.setFloat("pointLights[0].linear", 0.09f);
        boxesShader.setFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        boxesShader.setVec3("pointLights[1].position", pointLightPositions[1]);
        boxesShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        boxesShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        boxesShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        boxesShader.setFloat("pointLights[1].constant", 1.0f);
        boxesShader.setFloat("pointLights[1].linear", 0.09f);
        boxesShader.setFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        boxesShader.setVec3("pointLights[2].position", pointLightPositions[2]);
        boxesShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        boxesShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        boxesShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        boxesShader.setFloat("pointLights[2].constant", 1.0f);
        boxesShader.setFloat("pointLights[2].linear", 0.09f);
        boxesShader.setFloat("pointLights[2].quadratic", 0.032f);
        // point light 4
        boxesShader.setVec3("pointLights[3].position", pointLightPositions[3]);
        boxesShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        boxesShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        boxesShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        boxesShader.setFloat("pointLights[3].constant", 1.0f);
        boxesShader.setFloat("pointLights[3].linear", 0.09f);
        boxesShader.setFloat("pointLights[3].quadratic", 0.032f);
        // spotLight
        boxesShader.setVec3("spotLight.position", camera.Position);
        boxesShader.setVec3("spotLight.direction", camera.Front);
        boxesShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        boxesShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        boxesShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        boxesShader.setFloat("spotLight.constant", 1.0f);
        boxesShader.setFloat("spotLight.linear", 0.09f);
        boxesShader.setFloat("spotLight.quadratic", 0.032f);
        boxesShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        boxesShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        boxesShader.setMat4("projection", projection);
        boxesShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        boxesShader.setMat4("model", model);

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap.ID);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap.ID);
        // render containers
        glBindVertexArray(cubeVAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            boxesShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // also draw the lamp object(s)
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            lightCubeShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // render
        // ------
        //glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ////updateWindowTitleWithFPS(window, deltaTime);

        //// configure transformation matrices
        //glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
        //glm::mat4 view = camera.GetViewMatrix();
        //asteroidShader.use();
        //asteroidShader.setMat4("projection", projection);
        //asteroidShader.setMat4("view", view);
        //planetShader.use();
        //planetShader.setMat4("projection", projection);
        //planetShader.setMat4("view", view);

        //// draw planet
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        //planetShader.setMat4("model", model);
        //planet.Draw(planetShader);

        //// draw meteorites
        //asteroidShader.use();
        //asteroidShader.setInt("texture_diffuse1", 0);
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, rock.textures_loaded[0].id); // note: we also made the textures_loaded vector public (instead of private) from the model class.
        //for (unsigned int i = 0; i < rock.meshes.size(); i++)
        //{
        //    glBindVertexArray(rock.meshes[i].VAO);
        //    glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(rock.meshes[i].indices.size()), GL_UNSIGNED_INT, 0, amount);
        //    glBindVertexArray(0);
        //}

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        // Rendering
// (Your code clears your framebuffer, renders your other stuff etc.)
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // (Your code calls glfwSwapBuffers() etc.)

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (!(ImGui::GetIO().WantCaptureKeyboard == 0 && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_3) == GLFW_PRESS))
    {
        if (!firstMouse)
        {
            firstMouse = true;
        }
        return;
    }
        
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (ImGui::GetIO().WantCaptureKeyboard != 0)
        return;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
        
    
}
