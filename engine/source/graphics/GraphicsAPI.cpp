#include "graphics/GraphicsAPI.h"
#include "graphics/ShaderProgram.h"
#include "render/Material.h"
#include"render/Mesh.h"
#include <iostream>
namespace eng
{
  std::shared_ptr<ShaderProgram> GraphicsAPI::CreateShaderProgram(const std::string &vertexSource,
                                                                  const std::string &fragmentSource)
  {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexSourceCStr = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSourceCStr, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      char infoLog[512];
      glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
      std::cerr << "Vertex shader error:\n"
                << infoLog << std::endl;
      return nullptr;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentSourceCStr = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourceCStr, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      char infoLog[512];
      glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
      std::cerr << "Fragment shader error:\n"
                << infoLog << std::endl;
      return nullptr;
    }

    GLuint shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);
    glLinkProgram(shaderProgramID);

    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success)
    {
      char infoLog[512];
      glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);
      std::cerr << "Shader link error:\n" << infoLog << std::endl;
      return nullptr;
    }
    return std::make_shared<ShaderProgram>(shaderProgramID);
  }


  GLuint GraphicsAPI::CreateVertexBuffer(const std::vector<float>vertices)
  {
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return VBO;

  }
  GLuint GraphicsAPI::CreateIndexBuffer(const std::vector<uint32_t>indeces)
  {
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indeces.size()*sizeof(uint32_t), indeces.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    return EBO;
  }
  void GraphicsAPI::SetClearColor(float r, float g, float b, float a)
  {
    glClearColor(r, g, b, a);
   
  }
  void GraphicsAPI::clearBuffers()
  {
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void GraphicsAPI::BindShaderProgram(ShaderProgram *shaderProgram)
  {
    if (shaderProgram)
    {
      shaderProgram->Bind();
    }
  }

  void GraphicsAPI::BindMaterial(Material *material)
  {
    if (material)
    {
      material->Bind();
    }
  }
  void GraphicsAPI::BindMesh(Mesh* mesh)
  {
    if(mesh){
      mesh->Bind();
    }
  }
  void GraphicsAPI::DrawMesh(Mesh* mesh)
  {
    if(mesh){
      mesh->Draw();
    }
  }
}

