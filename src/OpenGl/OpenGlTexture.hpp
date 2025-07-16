#pragma once
#include"Graphics/Texture.hpp"
namespace Knight {
	
	class KNIGHT_ENGINE_API OpenGLTexture2D : public Texture2D
	{
		OpenGLTexture2D(std::string& path);
		~OpenGLTexture2D();

		
		virtual void Bind(unsigned int slot = 0) const ;
		virtual void Bind() ;
		virtual void Unbind() const ;
		virtual uint32_t GetWidth() const ;
		virtual uint32_t GetHeight() const ;
		virtual unsigned int  GetID() const ;
	private:
		uint32_t m_Width, m_Height;
		std::string Path;
		unsigned int TexID;
		uint32_t m_RendererID;
	};
	
}


