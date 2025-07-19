#include "OpenGlTexture.hpp"
#include "glad/glad.h"
#include "stb_image.h"
#include <filesystem>

namespace Knight {
    OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : Path(path)
    {
        stbi_set_flip_vertically_on_load(true);
        int width, height, channels;
        stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        std::string info = "Failed to load image: " + path;
        KE_CORE_ASSERT(data, info.c_str());

        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        switch (channels) {
        case 4: internalFormat = GL_RGBA8; dataFormat = GL_RGBA; break;
        case 3: internalFormat = GL_RGB8;  dataFormat = GL_RGB;  break;
        case 2: internalFormat = GL_RG8;   dataFormat = GL_RG;   break;
        case 1: internalFormat = GL_R8;    dataFormat = GL_RED;  break;
        default:
            stbi_image_free(data);
            std::string p = "Unsupported image channel count: " + std::to_string(channels);
           // KE_CORE_ASSERT(false, p.c_str() );
        }
      
        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(unsigned int slot) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }

    void OpenGLTexture2D::Unbind() const
    {
    }

    uint32_t OpenGLTexture2D::GetWidth() const
    {
        return m_Width;
    }

    uint32_t OpenGLTexture2D::GetHeight() const
    {
        return m_Height;
    }

    unsigned int OpenGLTexture2D::GetID() const
    {
        return m_RendererID;
    }
}