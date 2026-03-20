#include"Game.h"
#include"TestObject.h"
#include"Player.h"
#include<iostream>
#include<memory>
#include <filesystem>
#include"JumpPlatform.h"
#include"Bullet.h"

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
    /*auto scene = eng::Scene::Load("scenes/scene.sc");
    m_scene=scene;

    eng::Engine::GetInstance().SetScene(scene.get());*/

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

    return true;
}

void Game::Update(float deltaTime)
{
    m_scene->Update(deltaTime); 
    
}

void Game::Destroy()
{

}