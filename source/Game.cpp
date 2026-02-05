#include"Game.h"
#include"TestObject.h"
#include<iostream>
#include<memory>
#include <filesystem>

bool Game::Init()
{

    auto& fs = eng::Engine::GetInstance().GetFileSystem();
    auto texture = eng::Texture::Load("brick.png");

    m_scene = new eng::Scene();
    eng::Engine::GetInstance().SetScene(m_scene);
    
    auto camera = m_scene->CreateObject("Camera");
    camera->AddComponent(new eng::CamraComponent());
    camera->SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
    camera->AddComponent(new eng::PlayerControllerComponent());
    m_scene->SetMainCamera(camera);
     
    m_scene->CreateObject<TestObject>("TestObject");


    auto material = eng::Material::Load("materials/brick.mat");

    
    auto mesh = eng::Mesh::CreateCube();
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

    
    
    auto gun = eng::GameObject::LoadGLTF("models/sten_gunmachine_carbine/scene.gltf");
    gun->SetParent(camera);
    gun->SetPosition(glm::vec3(0.75f, -0.5f, -0.75f));
    gun->SetScale(glm::vec3(-1.0f, 1.0f, 1.0f));
    
    auto light = m_scene->CreateObject("Light");
    auto lightComp = new eng::LightComponent();
    lightComp->SetColor(glm::vec3(1.0f));
    light->AddComponent(lightComp);
    light->SetPosition(glm::vec3(-5.0f, 5.0f, 5.0f));



    

    return true;
}

void Game::Update(float deltaTime)
{
    m_scene->Update(deltaTime); 
}

void Game::Destroy()
{

}