#include "Game.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

bool Game::Init()
{
    auto& graphicsAPI = eng::Engine::GetInstance().GetGraphicsAPI();

    // =========================
    // SHADER 1 (Move + Scale)
    // =========================
    std::string vertexSrc1 = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 color;

        uniform vec2 uOffset;
        uniform vec2 uScale;

        out vec3 vColor;

        void main()
        {
            vColor = color;
            gl_Position = vec4(
                position.x * uScale.x + uOffset.x,
                position.y * uScale.y + uOffset.y,
                position.z,
                1.0
            );
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core
        in vec3 vColor;
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(vColor, 1.0);
        }
    )";

    auto shader1 = graphicsAPI.CreateShaderProgram(vertexSrc1, fragmentSrc);

    materials["object_1"] = std::make_shared<eng::Material>();
    materials["object_1"]->SetShaderProgram(shader1);

    // =========================
    // SHADER 2 (Rotation + Color)
    // =========================
    std::string vertexSrc2 = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 color;

        uniform vec2 uOffset;
        uniform vec2 uRotation; // x = angle, y = color multiplier

        out vec3 vColor;

        void main()
        {
            float a = uRotation.x;
            mat2 rot = mat2(
                cos(a), -sin(a),
                sin(a),  cos(a)
            );

            vec2 rotated = rot * position.xy;
            vColor = color * uRotation.y;

            gl_Position = vec4(
                rotated.x + uOffset.x,
                rotated.y + uOffset.y,
                position.z,
                1.0
            );
        }
    )";

    auto shader2 = graphicsAPI.CreateShaderProgram(vertexSrc2, fragmentSrc);

    materials["object_2"] = std::make_shared<eng::Material>();
    materials["object_2"]->SetShaderProgram(shader2);

    // =========================
    // MESH DATA
    // =========================
    std::vector<float> vertices =
    {
         0.2f,  0.2f, 0.0f, 1, 0, 0,
        -0.2f,  0.2f, 0.0f, 0, 1, 0,
        -0.2f, -0.2f, 0.0f, 0, 0, 1,
         0.2f, -0.2f, 0.0f, 1, 1, 0
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 2, 3
    };

    eng::VertexLayout layout;
    layout.elements.push_back({ 0, 3, GL_FLOAT, 0 });
    layout.elements.push_back({ 1, 3, GL_FLOAT, sizeof(float) * 3 });
    layout.stride = sizeof(float) * 6;

    meshes["object_1"] = std::make_unique<eng::Mesh>(layout, vertices, indices);
    meshes["object_2"] = std::make_unique<eng::Mesh>(layout, vertices, indices);

    // =========================
    // GAME OBJECTS
    // =========================
    gameObjects["object_1"] = {};
    gameObjects["object_2"] = { -0.6f, 0.6f };

    return true;
}

void Game::Update(float deltaTime)
{
    auto cmd1 = UpdateControllableObject("object_1", deltaTime);
    auto cmd2 = UpdateObject("object_2", deltaTime);

    auto& rq = eng::Engine::GetInstance().GetRenderQueue();
    rq.Submit(cmd1);
    rq.Submit(cmd2);
}

void Game::Destroy()
{
    materials.clear();
    meshes.clear();
    gameObjects.clear();
}

eng::RenderCommand Game::UpdateControllableObject(const std::string& name, float deltaTime)
{
    auto& input = eng::Engine::GetInstance().GetInputManager();
    auto& obj = gameObjects.at(name);

    const float speed = 0.5f;

    if (input.IsKeyPressed(GLFW_KEY_A)) obj.offsetX -= speed * deltaTime;
    if (input.IsKeyPressed(GLFW_KEY_D)) obj.offsetX += speed * deltaTime;
    if (input.IsKeyPressed(GLFW_KEY_W)) obj.offsetY += speed * deltaTime;
    if (input.IsKeyPressed(GLFW_KEY_S)) obj.offsetY -= speed * deltaTime;

    auto& mat = *materials.at(name);
    mat.SetParam("uOffset", obj.offsetX, obj.offsetY);
    mat.SetParam("uScale", obj.scaleX, obj.scaleY);

    eng::RenderCommand cmd;
    cmd.material = &mat;
    cmd.mesh = meshes.at(name).get();
    return cmd;
}

eng::RenderCommand Game::UpdateObject(const std::string& name, float deltaTime)
{
    auto& obj = gameObjects.at(name);

    obj.rotation += deltaTime;
    obj.colorMul = 0.5f * (std::sin(obj.rotation) + 1.0f);

    auto& mat = *materials.at(name);
    mat.SetParam("uOffset", obj.offsetX, obj.offsetY);
    mat.SetParam("uRotation", obj.rotation, obj.colorMul);

    eng::RenderCommand cmd;
    cmd.material = &mat;
    cmd.mesh = meshes.at(name).get();
    return cmd;
}
