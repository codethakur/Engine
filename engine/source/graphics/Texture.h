#pragma once
#include <glad/glad.h>
#include<memory>
#include<unordered_map>
#include <string>   
namespace eng
{
    class Texture
    {
    public:
        Texture(int width, int height, int numChannels, unsigned char* data);
        GLuint GetID() const;
        static std::shared_ptr<Texture>Load(const std::string& path);
        void Init(int width, int height, int numChannels, unsigned char* data);
        ~Texture();
    private:
        int m_width = 0;
        int m_height = 0;
        int m_numChannel = 0;
        GLuint m_textureID = 0;

    };
    class  TextureManger
    {
    public:
        std::shared_ptr<Texture>GetOrLoadTexture(const std::string& path);
    private:
        std::unordered_map<std::string, std::shared_ptr<Texture>>m_textures;
    };
}