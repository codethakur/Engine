#pragma once
#include"eng.h"
#include<memory>
#include <imgui.h>
enum class GameState
{
    MainMenu,
    Playing,
    Paused
};

class Game : public eng::Application
{
public:
    void RegisterTypes() override;
    bool Init() override;
    void Update(float deltaTime) override;
    void Destroy() override;

private:
    void RenderHUD();
    void RenderPauseMenu();
    void RenderSettingsWindow();
    
    std::shared_ptr<eng::Scene> m_scene;
    eng::GameObject* m_3DRoot = nullptr;
    GameState m_state = GameState::MainMenu;

    int m_health = 100;
    int m_ammo = 30;

    bool m_showSettings = false;
    float m_bgColor[3] = {64.0f/255.0f, 64.0f/255.0f, 64.0f/255.0f};
    float m_brightness = 1.0f;
    float m_musicVolume = 1.0f;
};