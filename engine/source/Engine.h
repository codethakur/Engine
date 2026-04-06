#pragma once
#include <memory>
#include <chrono>
#include <input/InputManager.h>

#include"graphics/GraphicsAPI.h"
#include"graphics/Texture.h"
#include"render/RenderQueue.h"
#include"scene/Scene.h"
#include"physics/physicsManager.h"
#include"io/FileSystem.h"
#include"audio/AudioManager.h"
#include"font/FontManager.h"
#include"scene/components/ui/UIInputSystem.h"


struct GLFWwindow;

namespace eng
{
    class Application;
    class Engine
    {
    public:
        static Engine &GetInstance();

    private:
        Engine() = default;
        Engine(const Engine &) = delete;
        Engine(Engine &&) = delete;
        Engine &operator=(Engine &) = delete;
        Engine &operator=(Engine &&) = delete;

    public:
        bool Init(int width, int height);
        void Run();
        void Destroy();
        void SetCursorEnabled(bool enabled);

        void SetApplication(Application* app);
        Application*  GetApplication();
        InputManager& GetInputManager();
        GraphicsAPI&  GetGraphicsAPI();
        RenderQueue&  GetRenderQueue();
        TextureManger& GetTextureManager();
        PhysicsManager& GetPhysicsManager();
        AudioManager& GetAudioManager();
        FontManager& GetFontManager();
        UIInputSystem& GetUIInputSystem();

        void SetScene(const std::shared_ptr<Scene>&scene);
        const std::shared_ptr<Scene>& GetScene();
        FileSystem& GetFileSystem();
        GLFWwindow* GetWindow() { return m_window; }

    private : 
        std::unique_ptr<Application> m_application;
        std::chrono::steady_clock::time_point m_lastTimePoint;
        GLFWwindow* m_window = nullptr;
        InputManager m_inputManager;
        GraphicsAPI m_graphicsAPI;
        RenderQueue m_renderQueue;
        FileSystem m_fileSystem;
        TextureManger m_textureManager;
        PhysicsManager m_physicsManager;
        AudioManager m_audiomManager;
        FontManager m_fontmanager;
        UIInputSystem m_uiInputSystem;
        std::shared_ptr<Scene> m_CurrentScreen;

    };
}