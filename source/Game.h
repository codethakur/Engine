#pragma once
#include"eng.h"
#include<memory>

class Game:public eng::Application
{
public:
    virtual bool Init() override;
    virtual void Update(float deltaTime ) override;
    virtual void Destroy() override;
private:
    eng::Scene* m_scene = nullptr;

};