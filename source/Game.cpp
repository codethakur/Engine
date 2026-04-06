#include<iostream>
#include<memory>
#include <filesystem>
#include <glad/glad.h> // before then GLFW  
#include<GLFW/glfw3.h>

#include"Game.h"
#include"TestObject.h"
#include"Player.h"

#include"JumpPlatform.h"
#include"Bullet.h"
#include "scene/components/ui/CanvasComponent.h"
#include "scene/components/ui/TextComponent.h"

void Game::RegisterTypes()
{
    Player::Register();
    Bullet::Register();
    JumpPlatform::Register();
}

bool Game::Init()
{
#if 0
    auto& fs = eng::Engine::GetInstance().GetFileSystem();
    auto texture = eng::Texture::Load("brick.png");

    m_scene = new eng::Scene();
    eng::Engine::GetInstance().SetScene(m_scene);
    auto player = m_scene->CreateObject<Player>("PPlayer");
    player->Init();

    m_scene->SetMainCamera(player);
     
    m_scene->CreateObject<TestObject>("TestObject");


    auto material = eng::Material::Load("materials/brick.mat");

    
    auto mesh = eng::Mesh::CreateBox();
    auto objectA = m_scene->CreateObject("ObjectA");
    objectA->AddComponent(new eng::MeshComponent(material, mesh));
    objectA->SetPosition(glm::vec3(1.0f, 2.0f, -5.0f));

    auto objectB = m_scene->CreateObject("ObjectB");
    objectB->AddComponent(new eng::MeshComponent(material, mesh));
    objectB->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
    objectB->SetRotation(glm::vec3(0.0f, 2.0f, 0.0f));

    auto objectC = m_scene->CreateObject("ObjectC");
    objectC->AddComponent(new eng::MeshComponent(material, mesh));
    objectC->SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
    objectC->SetRotation(glm::vec3(1.0f, 0.0f, 1.0f));
    objectC->SetScale(glm::vec3(1.5f, 1.5f, 1.5f));

    auto objectD = m_scene->CreateObject("ObjectD");
    objectD->AddComponent(new eng::MeshComponent(material, mesh));
    objectD->SetPosition(glm::vec3(2.0f, 1.0f, 0.0f));
    objectD->SetRotation(glm::vec3(1.0f, 0.0f, 1.0f));
    objectD->SetScale(glm::vec3(1.5f, 1.5f, 1.5f));

    /* auto suzanneMesh = eng::Mesh::Load("models/Suzanne.gltf");
    auto suzanneMaterial = eng::Material::Load("materials/suzanne.mat");

    auto suzanneObj = m_scene->CreateObject("Suzanne");
    suzanneObj->AddComponent(new eng::MeshComponent(suzanneMaterial, suzanneMesh));
    suzanneObj->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));*/

    auto suzanneObj = eng::GameObject::LoadGLTF("models/suzanne/Suzanne.gltf");
    suzanneObj->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));

    
    
   
    
    auto light = m_scene->CreateObject("Light");
    auto lightComp = new eng::LightComponent();
    lightComp->SetColor(glm::vec3(1.0f));
    light->AddComponent(lightComp);
    light->SetPosition(glm::vec3(-5.0f, 5.0f, 5.0f));

    auto ground = m_scene->CreateObject("Ground");
    ground->SetPosition(glm::vec3(0.0f, -5.0f, 0.0f));

    glm::vec3 groundExtents(20.0f, 2.0f, 20.0f);
    auto groundMesh = eng::Mesh::CreateBox(groundExtents);
    ground->AddComponent(new eng::MeshComponent(material, groundMesh));

    auto groundCollider = std::make_shared<eng::BoxCollider>(groundExtents);
    auto groundBody = std::make_shared<eng::RigidBody>(eng::BodyType::Static, groundCollider, 0.0f, 0.5f);
    ground->AddComponent(new eng::PhysicsComponent(groundBody));
    auto boxObj = m_scene->CreateObject("FallingBox");
    boxObj->AddComponent(new eng::MeshComponent(material, mesh));
    boxObj->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
    boxObj->SetRotation(glm::quat(glm::vec3(1.0f, 2.0f, 0.0f)));
    auto boxCollider = std::make_shared<eng::BoxCollider>(glm::vec3(1.0f));
    auto boxBody = std::make_shared<eng::RigidBody>(eng::BodyType::Dynamic, boxCollider, 5.0f, 0.9f);
    boxObj->AddComponent(new eng::PhysicsComponent(boxBody));

  
    //camera->SetPosition(glm::vec3(0.0f, 1.0f, 7.0f));
#endif
    auto scene = eng::Scene::Load("scenes/scene.sc");
    m_scene=scene;


    auto& engine = eng::Engine::GetInstance();

    engine.GetInstance().SetScene(m_scene);
    
    m_3DRoot = m_scene->FindObjectByName("3DRoot");
    if (m_3DRoot)
    {
        m_3DRoot->SetActive(false);
    }

    auto canvasComponent = engine.GetInstance().GetUIInputSystem().GetCanvas();
    if (!canvasComponent)
    {
        return false;
    }

    canvasComponent->SetActive(true);
    engine.SetCursorEnabled(true);
    engine.GetUIInputSystem().SetActive(true);

    if (auto button = canvasComponent->GetOwner()->FindChildByName("PlayButton"))
    {
        if (auto component = button->GetComponent<eng::ButtonComponent>())
        {
            component->onClick = [this]()
                {
                    auto& engine = eng::Engine::GetInstance();
                    engine.GetUIInputSystem().GetCanvas()->SetActive(false);
                    engine.SetCursorEnabled(false);

                    if (m_3DRoot)
                    {
                        m_3DRoot->SetActive(true);
                    }
                };
        }
    }

    if (auto button = canvasComponent->GetOwner()->FindChildByName("QuitButton"))
    {
        if (auto component = button->GetComponent<eng::ButtonComponent>())
        {
            component->onClick = [this]()
                {
                    SetNeedsToBeClosed(true);
                };
        }
    }

    
    #if 0
    m_scene = std::make_shared<eng::Scene>();
    eng::Engine::GetInstance().SetScene(m_scene.get());

    auto sprite = m_scene->CreateObject("Sprite");
    auto spriteComponent = new eng::SpriteComponent();

    auto texture = eng::Texture::Load("textures/brick.png");
    spriteComponent->SetTexture(texture);

    sprite->AddComponent(spriteComponent);
    sprite->SetPosition2D(glm::vec2(500.0f, 500.0f));

    spriteComponent->SetSize(glm::vec2(200.0f, 100.0f));
    spriteComponent->SetUpperRightUV(glm::vec2(2.0f, 1.0f));
    sprite->SetRotation2D(glm::radians(45.0f));


    auto camera = m_scene->CreateObject("Camera");
    auto cameraComponent = new eng::CameraComponent();
    camera->AddComponent(cameraComponent);
    m_scene->SetMainCamera(camera);

    auto canvas = m_scene->CreateObject("Canvas");
    auto canvasComponent = new eng::CanvasComponent();
    canvas->AddComponent(canvasComponent);

    auto& uiInput = eng::Engine::GetInstance().GetUIInputSystem();
    uiInput.SetActive(true);
    uiInput.SetCanvas(canvasComponent);

    auto button = m_scene->CreateObject("Button", canvas);
    button->SetPosition2D(glm::vec2(300.0f, 300.0f));
    auto buttonComponent = new eng::ButtonComponent();
    buttonComponent->SetRect(glm::vec2(150.0f, 50.0f));
    buttonComponent->SetColor(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
    button->AddComponent(buttonComponent);
    // After creating button

    auto text = m_scene->CreateObject("Text", canvas);
    text->SetPosition2D(glm::vec2(300.0f, 300.0f));
    auto textComponent = new eng::TextComponent();
    text->AddComponent(textComponent);
    textComponent->SetText("Some Text");
    textComponent->SetFont("fonts/arial.ttf", 24);
    textComponent->SetColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    #endif

        eng::Engine::GetInstance().GetGraphicsAPI().SetClearColor(
            64.0f/255.0f, 64.0f/255.0f, 64.0f/255.0f, 1.0f
        );
    return true;
}

void Game::Update(float deltaTime)
{
    auto& engine = eng::Engine::GetInstance();
    if (engine.GetInputManager().IsKeyPressed(GLFW_KEY_ESCAPE))
    {
        if (m_3DRoot && m_3DRoot->IsActive())
        {
            engine.GetUIInputSystem().GetCanvas()->SetActive(true);
            engine.SetCursorEnabled(true);
            m_3DRoot->SetActive(false);
        }
    }
    m_scene->Update(deltaTime); 
    
}

void Game::Destroy()
{
 m_scene.reset();
}