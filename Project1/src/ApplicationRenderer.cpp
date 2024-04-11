#include"ApplicationRenderer.h"

#include "SceneManager/Scenes/SceneOne.h"
#include "SceneManager/Scenes/SceneTwo.h"
#include "SceneManager/Scenes/SceneThree.h"
#include "SceneManager/Scenes/SceneFour.h"

ApplicationRenderer::ApplicationRenderer()
{
    sceneViewcamera = new Camera();
    sceneViewcamera->name = "Sceneview Camera";

    gameScenecamera = new Camera();
    gameScenecamera->name = "GameScene Camera";

    renderTextureCamera = new Camera();
    renderTextureCamera->name = "RenderTexture Camera";
}

ApplicationRenderer::~ApplicationRenderer()
{
}



void ApplicationRenderer::WindowInitialize(int width, int height,  std::string windowName)
{
    windowWidth = width;
    WindowHeight = height;
    lastX = windowWidth / 2.0f;
    lastY= WindowHeight / 2.0f;

    glfwInit();



    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int x, int y)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(w))->SetViewPort(w, x, y);
        });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->KeyCallBack(window, key, scancode, action, mods);
        });


    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xposIn, double yposIn)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseCallBack(window, xposIn, yposIn);
        });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseHeldCallBack(window, button, action, mods);
        });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseScroll(window, xoffset, yoffset);
        });
   
   

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.FontGlobalScale = 2.0f;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init("#version 450");
   // ImGui_ImplOpenGL3_Init("#version 130");

    //Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Query and print OpenGL version
    const GLubyte* version = glGetString(GL_VERSION);
    if (version) {
        std::cout << "OpenGL Version: " << version << std::endl;
    }
    else 
    {
        std::cerr << "Failed to retrieve OpenGL version\n";
     
    }


    FrameBufferSpecification specification;

    specification.width = windowWidth;
    specification.height = WindowHeight;
    specification.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH };
    

    sceneViewframeBuffer = new FrameBuffer(specification);

    gameframeBuffer = new FrameBuffer(specification);

    EditorLayout::GetInstance().applicationRenderer = this;
  

    InitializeShaders();
   
    GraphicsRender::GetInstance().InitializeGraphics();

    DebugModels::GetInstance().defaultCube = new Model("Models/DefaultCube/DefaultCube.fbx", false, true);
    DebugModels::GetInstance().defaultSphere = new Model("Models/DefaultSphere/DefaultSphere.fbx", false, true);
    DebugModels::GetInstance().defaultQuad = new Model("Models/DefaultQuad/DefaultQuad.fbx", false, true);

    InitializeSkybox();

    GraphicsRender::GetInstance().SetCamera(sceneViewcamera);

    sceneViewcamera->InitializeCamera(CameraType::PERSPECTIVE, 45.0f, 0.1f, 100.0f);
    sceneViewcamera->transform.position = glm::vec3(0, 1.00, 5);
    sceneViewcamera->transform.SetRotation(glm::vec3(0));

    gameScenecamera->InitializeCamera(CameraType::PERSPECTIVE, 45.0f, 0.1f, 100.0f);
    gameScenecamera->transform.position = glm::vec3(0, 1.00, 5);
    gameScenecamera->transform.SetRotation(glm::vec3(0));

    renderTextureCamera->InitializeCamera(CameraType::PERSPECTIVE, 45.0f, 0.1f, 100.0f);
    renderTextureCamera->transform.position = glm::vec3(0, 0, -1.0f);

    renderTextureCamera->IntializeRenderTexture(specification);
  
    sceneViewcamera->postprocessing->InitializePostProcessing();
    gameScenecamera->postprocessing->InitializePostProcessing();

    isImguiPanelsEnable = true;

    SceneManager::GetInstance().application = this;

    PhysXEngine::GetInstance().InitializePhysX();
}

void ApplicationRenderer::InitializeShaders()
{
    defaultShader = new Shader("Shaders/DefaultShader_Vertex.vert", "Shaders/DefaultShader_Fragment.frag");
   
    solidColorShader = new Shader("Shaders/SolidColor_Vertex.vert", "Shaders/SolidColor_Fragment.frag", SOLID);
    stencilShader = new Shader("Shaders/StencilOutline.vert", "Shaders/StencilOutline.frag", OPAQUE);
    //ScrollShader = new Shader("Shaders/ScrollTexture.vert", "Shaders/ScrollTexture.frag");

    alphaBlendShader = new Shader("Shaders/DefaultShader_Vertex.vert", "Shaders/DefaultShader_Fragment.frag", ALPHA_BLEND);
    alphaBlendShader->blendMode = ALPHA_BLEND;

    alphaCutoutShader = new Shader("Shaders/DefaultShader_Vertex.vert", "Shaders/DefaultShader_Fragment.frag", ALPHA_CUTOUT);
    alphaCutoutShader->blendMode = ALPHA_CUTOUT;

    skyboxShader = new Shader("Shaders/SkyboxShader.vert", "Shaders/SkyboxShader.frag");
    skyboxShader->modelUniform = false;

    boneAnimationShader = new Shader("Shaders/AnimationShader.vert", "Shaders/AnimationShader.frag");
    boneAnimationShader->blendMode = OPAQUE;

    defaultInstanceShader = new Shader("Shaders/MeshInstanceShader.vert", "Shaders/MeshInstanceShader.frag");
    defaultInstanceShader->blendMode = OPAQUE;
    defaultInstanceShader->modelUniform = false;

    grassInstanceShader = new Shader("Shaders/Grass/GrassMeshInstanceShader.vert", "Shaders/Grass/GrassMeshInstanceShader.frag", ALPHA_CUTOUT);
    grassInstanceShader->modelUniform = false;

    GraphicsRender::GetInstance().defaultShader = defaultShader;
    GraphicsRender::GetInstance().solidColorShader = solidColorShader;
    GraphicsRender::GetInstance().stencilShader = stencilShader; 
    GraphicsRender::GetInstance().boneAnimationShader = boneAnimationShader;
    GraphicsRender::GetInstance().alphaBlendShader = alphaBlendShader;
    GraphicsRender::GetInstance().alphaCutoutShader = alphaCutoutShader;
    GraphicsRender::GetInstance().defaultInstanceShader = defaultInstanceShader;
    GraphicsRender::GetInstance().grassInstanceShader = grassInstanceShader;
}

void ApplicationRenderer::InitializeSkybox()
{
    skyBoxModel = new Model("Models/DefaultCube/DefaultCube.fbx", false, true);
    skyBoxModel->meshes[0]->meshMaterial = new SkyboxMaterial();

    skyBoxMaterial = skyBoxModel->meshes[0]->meshMaterial->skyboxMaterial();

    std::vector<std::string> faces
    {
       ("Textures/skybox/right.jpg"),
       ("Textures/skybox/left.jpg"),
       ("Textures/skybox/top.jpg"),
       ("Textures/skybox/bottom.jpg"),
       ("Textures/skybox/front.jpg"),
       ("Textures/skybox/back.jpg")
    };

    skyBoxMaterial->skyBoxTexture->LoadTexture(faces);

    GraphicsRender::GetInstance().SkyBoxModel = skyBoxModel;
}



void ApplicationRenderer::Start()
{

    BaseScene* sceneOne = new SceneOne("SceneOne");
    BaseScene* sceneTwo = new SceneTwo("SceneTwo");
    BaseScene* sceneThree = new SceneThree("SceneThree");
    BaseScene* sceneFour = new SceneFour("SceneFour");

    SceneManager::GetInstance().OnChangeScene("SceneFour");
}


void ApplicationRenderer::Render()
{
   
    Start();
  
    EditorLayout::GetInstance().InitializeEditors();

    Time::GetInstance().lastFrame = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        Time::GetInstance().SetCurrentTime(glfwGetTime());

        EngineGameLoop();

        EngineGraphicsRender();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ShutDown();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void ApplicationRenderer::EngineGraphicsRender()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();

    if (isImguiPanelsEnable)
    {
        PanelManager::GetInstance().Update((float)windowWidth, (float)WindowHeight);
    }

    RenderForCamera(sceneViewcamera, sceneViewframeBuffer);

    for (Camera* camera :  CameraManager::GetInstance().GetCameras())
    {
        if (camera->renderTexture == nullptr)
        {
            RenderForCamera(camera, gameframeBuffer);
        }
        else
        {
            RenderForCamera(camera, camera->renderTexture->framebuffer); 
        }
       
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void ApplicationRenderer::EngineGameLoop()
{
    MouseInputUpdate();
    ProcessInput(window);

    if (isPlayMode)
    {
        EntityManager::GetInstance().Update(Time::GetInstance().deltaTime);
        InputManager::GetInstance().Update(Time::GetInstance().deltaTime);
        SceneManager::GetInstance().Update();
        ParticleSystemManager::GetInstance().Update(Time::GetInstance().deltaTime);
    }

    PostRender();
}
void ApplicationRenderer::RenderForCamera(Camera* camera, FrameBuffer* framebuffer)
{

    framebuffer->Bind();

    GraphicsRender::GetInstance().Clear();

    projection = camera->GetProjectionMatrix();

    view = camera->GetViewMatrix();

    skyBoxView = glm::mat4(glm::mat3(camera->GetViewMatrix()));


    defaultShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(defaultShader);

    defaultShader->setMat4("projection", projection);
    defaultShader->setMat4("view", view);
    defaultShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    defaultShader->setFloat("time", scrollTime);
    defaultShader->setBool("isDepthBuffer", false);

    boneAnimationShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(boneAnimationShader);
    boneAnimationShader->setMat4("projection", projection);
    boneAnimationShader->setMat4("view", view);
    boneAnimationShader->setVec3("viewPos", sceneViewcamera->transform.position.x, sceneViewcamera->transform.position.y, sceneViewcamera->transform.position.z);
    boneAnimationShader->setBool("isDepthBuffer", false);


    alphaBlendShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(alphaBlendShader);
    alphaBlendShader->setMat4("projection", projection);
    alphaBlendShader->setMat4("view", view);
    alphaBlendShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    alphaBlendShader->setFloat("time", scrollTime);
    alphaBlendShader->setBool("isDepthBuffer", false);

    alphaCutoutShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(alphaCutoutShader);
    alphaCutoutShader->setMat4("projection", projection);
    alphaCutoutShader->setMat4("view", view);
    alphaCutoutShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    alphaCutoutShader->setFloat("time", scrollTime);
    alphaCutoutShader->setBool("isDepthBuffer", false);

    defaultInstanceShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(defaultInstanceShader);

    defaultInstanceShader->setMat4("projection", projection);
    defaultInstanceShader->setMat4("view", view);
    defaultInstanceShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    defaultInstanceShader->setFloat("time", scrollTime);
    defaultInstanceShader->setBool("isDepthBuffer", false);

    grassInstanceShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(grassInstanceShader);

    grassInstanceShader->setMat4("projection", projection);
    grassInstanceShader->setMat4("view", view);
    grassInstanceShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);

    solidColorShader->Bind();
    solidColorShader->setMat4("projection", projection);
    solidColorShader->setMat4("view", view);

    stencilShader->Bind();
    stencilShader->setMat4("projection", projection);
    stencilShader->setMat4("view", view);

    glDepthFunc(GL_LEQUAL);
    skyboxShader->Bind();
    skyboxShader->setMat4("projection", projection);
    skyboxShader->setMat4("view", skyBoxView);

    GraphicsRender::GetInstance().SkyBoxModel->Draw(skyboxShader);
    glDepthFunc(GL_LESS);


    EntityManager::GetInstance().Render();

    SceneManager::GetInstance().Render();

    GraphicsRender::GetInstance().Draw();

    ParticleSystemManager::GetInstance().Render();

    if (camera->isPostprocessing)
    {
        camera->postprocessing->ApplyPostprocessing(framebuffer);
    }

     framebuffer->Unbind();
}

void ApplicationRenderer::ChangeCursorState(eCursorState state)
{
    currentCursorState = state;
    switch (currentCursorState)
    {
    case eCursorState::VISIBLE:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        break;
    case eCursorState::HIDDEN:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        break;
    case eCursorState::LOCKED:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        break;
    }
}

void ApplicationRenderer::PostRender()
{
    if (isPlayMode)
    {
        PhysXEngine::GetInstance().InitializePhysXObjects();
        PhysXEngine::GetInstance().Update(Time::GetInstance().deltaTime);
    }
}

void ApplicationRenderer::Clear()
{
    GLCALL(glClearColor(0.1f, 0.1f, 0.1f, 0.1f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
   //glStencilMask(0x00);
}

void ApplicationRenderer::ShutDown()
{

    PhysXEngine::GetInstance().ShutDown();
    SceneManager::GetInstance().ShutDown();
}

void ApplicationRenderer::ProcessInput(GLFWwindow* window)
{

    float cameraSpeed=25;

    if (EditorLayout::GetInstance().IsViewportHovered())
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            sceneViewcamera->ProcessKeyboard(FORWARD, Time::GetInstance().deltaTime * cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            sceneViewcamera->ProcessKeyboard(BACKWARD, Time::GetInstance().deltaTime * cameraSpeed);
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            sceneViewcamera->ProcessKeyboard(LEFT, Time::GetInstance().deltaTime * cameraSpeed);

        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            sceneViewcamera->ProcessKeyboard(RIGHT, Time::GetInstance().deltaTime * cameraSpeed);

        }
    }

}


 void ApplicationRenderer::SetViewPort(GLFWwindow* window, int width, int height)
{
 //   glViewport(0, 0, width, height);
}

 void ApplicationRenderer::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
 {  
     
         if (action == GLFW_PRESS)
         {
             if (key == GLFW_KEY_ESCAPE)
             {
                 ChangeCursorState(eCursorState::VISIBLE);
             }
             
             InputManager::GetInstance().OnKeyPressed(key);
         }
         else if(action == GLFW_RELEASE)
         {
             InputManager::GetInstance().OnKeyReleased(key);
         }
         else if (action == GLFW_REPEAT)
         {
            // InputManager::GetInstance().OnkeyHold(key);
         }
     
 }

 void ApplicationRenderer::MouseCallBack(GLFWwindow* window, double xposIn, double yposIn)
 {

        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);
     
      
        currentMousePos.x = xpos;
        currentMousePos.y = ypos;

        mouseDeltaPos = currentMousePos - lastMousePos;
        mouseDeltaPos.y = -mouseDeltaPos.y;

        InputManager::GetInstance().mouseCurrentPosition = currentMousePos;
     
     
        lastMousePos.x = xpos;
        lastMousePos.y = ypos;

         if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && EditorLayout::GetInstance().IsViewportHovered())
         {
            sceneViewcamera->ProcessMouseMovement(mouseDeltaPos.x, mouseDeltaPos.y);
         }

 }

 void ApplicationRenderer::MouseHeldCallBack(GLFWwindow* window, int& button, int& action, int& mods)
 {
     if (action == GLFW_PRESS)
     {
         InputManager::GetInstance().OnMouseButtonPressed(button);
     }
     else if (action == GLFW_RELEASE)
     {
         InputManager::GetInstance().OnMouseButtonReleased(button);
     }
 }

 void ApplicationRenderer::MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
 {
     sceneViewcamera->ProcessMouseScroll(static_cast<float>(yoffset));
 }

 void ApplicationRenderer::MouseInputUpdate()
 {

      // Calculate the raw mouse delta
     glm::vec2 rawMouseDelta = InputManager::GetInstance().mouseCurrentPosition - InputManager::GetInstance().mouseLastPosition;

     // Invert Y-axis
     rawMouseDelta.y = -rawMouseDelta.y;

     // Apply smoothing (exponential smoothing)
  
     glm::vec2 smoothedMouseDelta = InputManager::GetInstance().smoothedMouseDelta * (1.0f - mouseSmoothingFactor) + rawMouseDelta * mouseSmoothingFactor;
     InputManager::GetInstance().smoothedMouseDelta = smoothedMouseDelta;

     InputManager::GetInstance().SetMouseSmoothDelta(smoothedMouseDelta);

     // Update the last mouse position for the next frame
     InputManager::GetInstance().mouseLastPosition = InputManager::GetInstance().mouseCurrentPosition;
 }