#pragma once
#include<memory>
#include<string>
#include<vector>
#include <glad/glad.h>

namespace eng
{
    class ShaderProgram;
    class Material;
    class Mesh;


    class GraphicsAPI
    {
    public:
        bool Init();
        std::shared_ptr<ShaderProgram> CreateShaderProgram(
        const std::string& vertexPath,
        const std::string& fragmentPath);
        const std::shared_ptr<ShaderProgram>& GetDefaultShaderProgram();
        GLuint CreateVertexBuffer(const std::vector<float>vertices);
        GLuint CreateIndexBuffer(const std::vector<uint32_t>indeces);

        void SetClearColor(float r, float g, float b, float a);
        void clearBuffers();

        void BindShaderProgram(ShaderProgram* shader);
        void BindMaterial(Material* material);
        void BindMesh(Mesh* mesh);
        void DrawMesh(Mesh* mesh);
    private:
    std::shared_ptr<ShaderProgram>m_defaultShaderProgram;
    };
}
