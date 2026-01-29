#pragma once
#include"scene/Component.h"

namespace eng
{
    class PlayerControllerComponent : public Component
    {
        COMPONENT(PlayerControllerComponent)
    public:
        void Update(float deltaTime) override;

    private:
    float m_sensitivity = 0.2f;
    float m_moveSpeed = 2.0f;

    };
};