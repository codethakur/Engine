#include"Engine.h"
#include"Application.h"
#include "input/InputManager.h"
#include"scene/Component.h"
#include"scene/components/CamraComponent.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
namespace eng
{
    void keyCallback(GLFWwindow *window, int key,  int, int action, int )
    {
        auto& inputManager = eng::Engine::GetInstance().GetInputManager();

        if (action == GLFW_PRESS)
        {
            inputManager.SetKeyPressed(key , true);
        }
        else if (action == GLFW_RELEASE)
        {
            inputManager.SetKeyPressed(key, false);
        }

    }
    void mouseButtonCallback(GLFWwindow* window, int button, int action, int)
    {
        auto& inputManager = eng::Engine::GetInstance().GetInputManager();

        if (action == GLFW_PRESS)
        {
            inputManager.SetMouseButtonPressed(button , true);
        }
        else if (action == GLFW_RELEASE)
        {
            inputManager.SetMouseButtonPressed(button, false);
        }
    }
    void currsorPositionCallback(GLFWwindow* window, double xpos, double ypos)
    {
        auto& inputManager = eng::Engine::GetInstance().GetInputManager();   
        inputManager.SetMousePositionOld(inputManager.GetMousePosittionCurrent());
        glm::vec2 currentPos(static_cast<float>(xpos), static_cast<float>(ypos)); 
        inputManager.SetMousePositionCurrent(currentPos); 

    }

    Engine& Engine::GetInstance()
    {
        static Engine instance;
        return instance;
    }

    bool Engine::Init(int width, int height)
    {
        if(!m_application){
            return false;
        }
        
        #if defined(__APPLE__)
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
        if (!glfwInit())
        {
            std::cerr << "GLFW init failed\n";
            return false;
        }

        // macOS core profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

       m_window = glfwCreateWindow(width, height, "Game Engine", nullptr, nullptr);

        if (!m_window)
        {
            std::cerr << "Window creation failed\n";
            glfwTerminate();
            return false;
        }
        glfwSetKeyCallback(m_window, keyCallback);
        glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
        glfwSetCursorPosCallback(m_window, currsorPositionCallback);

        

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD\n";
            return false;
        }
        int fbWidth, fbHeight;
        glfwGetFramebufferSize(m_window, &fbWidth, &fbHeight);
        glViewport(0, 0, fbWidth, fbHeight);

        m_graphicsAPI.Init();
        m_physicsManager.Init();
        return m_application->Init();
    }

    void Engine::Run()
    {
        if(!m_application){
            return;
        }
        m_lastTimePoint = std::chrono::high_resolution_clock::now();   
        while(!glfwWindowShouldClose(m_window) && !m_application->NeedToBeClosed())
        {
            glfwPollEvents();

            auto now =  std::chrono::high_resolution_clock::now();  
            float deltaTime = std::chrono::duration<float>(now - m_lastTimePoint).count();
            m_lastTimePoint = now;
            m_physicsManager.Update(deltaTime);
            m_application->Update(deltaTime);

            m_graphicsAPI.SetClearColor(0.25f, 0.25f, 0.25f, 1.0f);
            m_graphicsAPI.clearBuffers();

            CameraData cameraData;
            std::vector<LightData>lights;
            int width = 0;
            int height = 0;
            glfwGetWindowSize(m_window, &width, &height);
            float aspect = static_cast<float>(width)/static_cast<float>(height);

            if(m_CurrentScreen)
            {
                if(auto cameraObject = m_CurrentScreen->GetMainCamera()){
                    //logic for Matrices
                    auto cameraComponent = cameraObject->GetComponent<CamraComponent>();
                    if(cameraComponent)
                    {
                        cameraData.viewMatrix = cameraComponent->GetViewMatrix();
                        cameraData.projectionMatrix = cameraComponent->GetProjectMatrix(aspect);
                        cameraData.position = cameraObject->GetWorldPosition();
                    }
                }
                lights = m_CurrentScreen->CollectLights(); 
            }

            m_renderQueue.Draw(m_graphicsAPI, cameraData, lights);

            glfwSwapBuffers(m_window);
            m_inputManager.SetMousePositionCurrent(m_inputManager.GetMousePosittionCurrent());

        }
    }

    void Engine::Destroy()
    {
        if(m_application){
            m_application->Destroy();
            m_application.reset();
            glfwTerminate();
            m_window = nullptr;
        }
    }

    void Engine::SetApplication(Application* app)
    {
       m_application.reset(app);
    }
    Application*Engine:: GetApplication()
    {
        return m_application.get();
    }
    
    InputManager& Engine::GetInputManager()
    {
        return m_inputManager;
    }
    GraphicsAPI& Engine::GetGraphicsAPI()
    {
        return m_graphicsAPI;
    }
    RenderQueue& Engine::GetRenderQueue()
    {
        return m_renderQueue;
    }
    TextureManger& Engine::GetTextureManager()
    {
        return m_textureManager;
    }
    PhysicsManager& Engine::GetPhysicsManager()
    {
        return m_physicsManager;
    }
    void Engine::SetScene(Scene* scene)
    {
        m_CurrentScreen.reset(scene);
    }
    FileSystem& Engine::GetFileSystem()
    {
       return m_fileSystem;
    }
    
    Scene* Engine::GetScene()
    {
        return m_CurrentScreen.get();
    }
    
}
