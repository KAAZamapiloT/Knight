#pragma once
#include"Graphics/Texture.hpp"
#include"KnightEnginepch.h"
namespace Knight {
	
	class KNIGHT_ENGINE_API OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t Width, uint32_t Height);
		virtual ~OpenGLTexture2D();

		
		virtual void Bind(unsigned int slot = 0) const ;
		virtual void SetData(void* data, uint32_t size) override;
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


