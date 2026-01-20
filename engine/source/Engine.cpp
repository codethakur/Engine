#include"Engine.h"
#include"Application.h"
#include "input/InputManager.h"
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

        glfwMakeContextCurrent(m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD\n";
            return false;
        }

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
            
            glClearColor(0.0f, 0.907f, 0.702f, 0.1f); 
            glClear(GL_COLOR_BUFFER_BIT);

            glfwPollEvents();

            auto now =  std::chrono::high_resolution_clock::now();  
            float deltaTime = std::chrono::duration<float>(now - m_lastTimePoint).count();
            m_lastTimePoint = now;

            m_application->Update(deltaTime);

            glfwSwapBuffers(m_window);

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
    
}
