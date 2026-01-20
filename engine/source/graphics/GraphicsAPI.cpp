#include"graphics/GraphicsAPI.h"
#include"graphics/ShaderProgram.h"
#include<iostream>
namespace eng
{
  std::shared_ptr<ShaderProgram>GraphicsAPI::CreateShaderProgram(const std::string& vertexSource, 
                                                                    const std::string& fragmentSource)
  {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSourceCStr = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSourceCStr, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Vertex shader error:\n"<< infoLog << std::endl;
        return nullptr;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSourceCStr = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSourceCStr, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Fragment shader error:\n" << infoLog << std::endl;
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
        std::cerr << "Shader link error:\n"<< infoLog << std::endl;
        return nullptr;
    }
    return std::make_shared<ShaderProgram>(shaderProgramID);
  }
  void GraphicsAPI::BindShaderProgram(ShaderProgram* shaderProgram)
  {
    shaderProgram->Bind();
  }
} 


