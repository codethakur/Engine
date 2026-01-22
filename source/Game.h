#pragma once

#include "eng.h"
#include <unordered_map>
#include <memory>
#include <string>

struct GameObject
{
    float offsetX = 0.0f;
    float offsetY = 0.0f;

    float scaleX = 1.0f;
    float scaleY = 1.0f;

    float rotation = 0.0f;
    float colorMul = 1.0f;
};

class Game : public eng::Application
{
public:
    bool Init() override;
    void Update(float deltaTime) override;
    void Destroy() override;

private:
    eng::RenderCommand UpdateControllableObject(const std::string& name, float deltaTime);
    eng::RenderCommand UpdateObject(const std::string& name, float deltaTime);

private:
    std::unordered_map<std::string, std::shared_ptr<eng::Material>> materials;
    std::unordered_map<std::string, std::unique_ptr<eng::Mesh>> meshes;
    std::unordered_map<std::string, GameObject> gameObjects;
};
