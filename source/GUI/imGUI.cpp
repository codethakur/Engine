#include "imGUI.h"
#include "Engine.h"

void imGUI::RenderHUD()
{
    ImGui::SetNextWindowPos(ImVec2(10,10), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(160,70), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.4f);
    ImGui::Begin("HUD", nullptr,
        ImGuiWindowFlags_NoTitleBar | 
        ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoScrollbar | 
        ImGuiWindowFlags_NoInputs | 
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoBringToFrontOnFocus
    ); 
    
    ImGui::TextColored(ImVec4(0.02f, 1.0f, 0.2f, 1.0f), "HP:   %d", m_health);
    ImGui::TextColored(ImVec4(0.02f, 0.8f, 0.2f, 1.0f), "Ammo: %d", m_health);
    ImGui::End();
}
void imGUI::RenderPauseMenu()
{
    ImGuiIO& io = ImGui::GetIO();

    ImVec2 center(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f);
    ImGui::SetNextWindowPos(center, ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(200, 160), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.85f);
    ImGui::Begin("Paused", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoScrollbar
    );

    ImGui::SetCursorPosX((200-120)*0.5f);
    if(ImGui::Button("Resume", ImVec2(120, 36)))
    {
        m_state = GameState::Playing;
        eng::Engine::GetInstance().SetCursorEnabled(false);

    }
    ImGui::Spacing();
    ImGui::SetCursorPosX((200-120) * 0.5 );
    if(ImGui::Button("Main Menu", ImVec2(120, 36)))
    {
        m_showSettings = !m_showSettings;
    }
        ImGui::Spacing();
    ImGui::SetCursorPosX((200 - 120) * 0.5f);
    if (ImGui::Button("Quit", ImVec2(120, 36)))
    {
        if (m_quitCallback) m_quitCallback();
    }

    ImGui::End();
}

void imGUI::RenderSettingsWindow()
{
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 settingsPos(
        io.DisplaySize.x * 0.5f + 120.0f,
        io.DisplaySize.y * 0.5f - 80.0f
    );
    ImGui::SetNextWindowPos(settingsPos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(280, 160), ImGuiCond_Always);
    ImGui::SetNextWindowBgAlpha(0.85f);
    ImGui::Begin("setting", nullptr,
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse
    );

    ImGui::SliderFloat("Brightness", &m_brightness, 0.0f, 2.0f);
    ImGui::Separator();
    ImGui::ColorEdit3("Background", m_bgColor);
    ImGui::Separator();
    ImGui::SliderFloat("Music Volume", &m_musicVolume, 0.0f, 1.0f);

    eng::Engine::GetInstance().GetGraphicsAPI().SetClearColor(
        m_bgColor[0] * m_brightness,
        m_bgColor[1] * m_brightness,
        m_bgColor[2] * m_brightness,
        1.0f
    );

    ImGui::End();
}