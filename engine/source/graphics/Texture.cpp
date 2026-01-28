#include"Texture.h"

namespace eng
{
    Texture::Texture(int width, int height, int numChannels, unsigned char* data)
        :m_width(width), m_height(height), m_numChannel(numChannels)
    {
        glGenTextures(1, &m_textureID);
        glBindTexture(GL_TEXTURE_2D, m_textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    }
    GLuint Texture::GetID() const
    {
        return m_textureID;
    }
    Texture::~Texture()
    {
        if(m_textureID>0)
        {
            glDeleteTextures(1, &m_textureID);
        }
    }
} 
