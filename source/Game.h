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
    eng::Material m_material;
    std::unique_ptr<eng::Mesh> m_mesh;
};