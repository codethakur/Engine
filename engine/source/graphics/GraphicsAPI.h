#pragma once
#include<memory>
#include<string>
#include <glad/glad.h>

namespace eng
{
    class ShaderProgram;
    class Material;
    class GraphicsAPI
    {
    public:
        std::shared_ptr<ShaderProgram> CreateShaderProgram(
            const std::string& vertexPath,
            const std::string& fragmentPath);

        void BindShaderProgram(ShaderProgram* shader);
        void BindMaterial(Material* material);
    };
}
