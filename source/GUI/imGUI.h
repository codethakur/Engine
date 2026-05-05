#pragma once
#include "eng.h"
#include <imgui.h>

enum class GameState
{
    MainMenu,
    Playing,
    Paused
};

class imGUI
{
public:
    void RenderHUD();
    void RenderPauseMenu();
    void RenderSettingsWindow();

    GameState GetState() const { return m_state; }
    void SetState(GameState state) { m_state = state; }

    bool ShowSettings() const { return m_showSettings; }
    
    std::function<void()> m_quitCallback;
private:
    GameState m_state = GameState::MainMenu;

    int m_health = 100;
    int m_ammo = 30;

    bool m_showSettings = false;
    float m_bgColor[3] = {64.0f/255.0f, 64.0f/255.0f, 64.0f/255.0f};
    float m_brightness = 1.0f;
    float m_musicVolume = 1.0f;
};