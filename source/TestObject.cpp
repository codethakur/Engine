#include"TestObject.h"
#include <GLFW/glfw3.h>
#include <algorithm> // for std::clamp


TestObject::TestObject()
{
    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 color;

        out vec3 vColor;
        uniform mat4 uModel;

        void main()
        {
            vColor = color;
            gl_Position = uModel * vec4(position, 1.0);
        }
    )";

    std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        in vec3 vColor;

        void main()
        {
            FragColor = vec4(vColor, 1.0);
        }
    )";

    auto& graphicsAPI = eng::Engine::GetInstance().GetGraphicsAPI();
    auto shaderProgram = graphicsAPI.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
    
    auto material = std::make_shared<eng::Material>();
    material->SetShaderProgram(shaderProgram);

    std::vector<float> vertices =
    {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        0, 2, 3
    };

    eng::VertexLayout vertexLayout;

    // Postion
    vertexLayout.elements.push_back({
        0, 
        3, 
        GL_FLOAT,
        0
        });
    // Color
    vertexLayout.elements.push_back({
        1,
        3,
        GL_FLOAT,
        sizeof(float) * 3
        });
    vertexLayout.stride = sizeof(float) * 6; 

    auto mesh = std::make_shared<eng::Mesh>(vertexLayout, vertices, indices);
    AddComponent(new eng::MeshComponent(material, mesh));

}

void TestObject::Update(float deltaTime)
{
    eng::GameObject::Update(deltaTime);

    auto position = GetPosition();
    auto& input = eng::Engine::GetInstance().GetInputManager();

    //Horizontal Movement
    if (input.IsKeyPressed(GLFW_KEY_A))
        position.x -= 0.01f;
    else if (input.IsKeyPressed(GLFW_KEY_D))
        position.x+= 0.01f;


    //Vertical movement
    if (input.IsKeyPressed(GLFW_KEY_W))
       position.y += 0.01f;
    else if (input.IsKeyPressed(GLFW_KEY_S))
      position.y -= 0.01f;

    position.x = std::clamp(position.x, -0.5f, 0.5f);
    position.y = std::clamp(position.y, -0.5f, 0.5f);

    SetPosition(position);

}