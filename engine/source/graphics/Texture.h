#pragma once
#include <glad/glad.h>
namespace eng
{
    class Texture
    {
    public:
        Texture(int width, int height, int numChannels, unsigned char* data);
        GLuint GetID() const;
        ~Texture();
    private:
        int m_width = 0;
        int m_height = 0;
        int m_numChannel = 0;
        GLuint m_textureID = 0;

    };
}