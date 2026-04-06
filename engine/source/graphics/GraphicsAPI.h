#pragma once



// #define GLFW_INCLUDE_NONE
// #include <GLFW/glfw3.h>

#include<memory>
#include<string>
#include<vector>
#include<unordered_map>
#include<glad/glad.h>
namespace eng
{
    class ShaderProgram;
    class Material;
    class Mesh;

    enum class BlendMode
    {
        Disabled,
        Alpha,
        Additive,
        Multiply
    };

    struct Rect 
    { 
        int x=0, y=0, width=0, height=0; 
    };
    struct ShaderKey
    {
        std::string vertexSource;
        std::string fragmentSource;

        bool operator==(const ShaderKey& other) const
        {
            return vertexSource == other.vertexSource &&
                fragmentSource == other.fragmentSource;
        }
    };

    struct ShaderKeyHash
    {
        std::size_t operator()(const ShaderKey& key) const
        {
            std::size_t h1 = std::hash<std::string>{}(key.vertexSource);
            std::size_t h2 = std::hash<std::string>{}(key.fragmentSource);
            return h1 ^ (h2 << 1);
        }
    };


    class GraphicsAPI
    {
    public:
        bool Init();
        std::shared_ptr<ShaderProgram> CreateShaderProgram(
        const std::string& vertexPath,
        const std::string& fragmentPath);

        const std::shared_ptr<ShaderProgram>& GetDefaultShaderProgram();
        const std::shared_ptr<ShaderProgram>& GetDefault2DShaderProgram();
        const std::shared_ptr<ShaderProgram>&GetDefaultUIShaderProgram();
       const Rect& GetViewport()const;

        GLuint CreateVertexBuffer(const std::vector<float>vertices);
        GLuint CreateIndexBuffer(const std::vector<uint32_t>indeces);

        void SetClearColor(float r, float g, float b, float a);
        void clearBuffers();
        void SetViewport(int x, int y, int width, int height);
        void SetDepthTestEnabled(bool enable);
        void SetBlendMode(BlendMode mode);


        void BindShaderProgram(ShaderProgram* shader);
        void BindMaterial(Material* material);
        void BindMesh(Mesh* mesh);
        void UnbindMesh(Mesh* mesh);
        void DrawMesh(Mesh* mesh);
    private:
        Rect m_viewport;
        std::shared_ptr<ShaderProgram>m_defaultShaderProgram;
        std::shared_ptr<ShaderProgram>m_default2DShaderProgram;
        std::shared_ptr<ShaderProgram> m_defaultUIShaderProgram;
        std::unordered_map<ShaderKey, std::shared_ptr<ShaderProgram>, ShaderKeyHash> m_shaderCache;
    };
}
