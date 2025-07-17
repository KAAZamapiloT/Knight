#pragma once
#include "EngineApi.hpp"
#include"KnightEnginepch.h"

namespace Knight {
	class KNIGHT_ENGINE_API Texture
	{
	public:
		Texture() = default;
		virtual ~Texture() = default;
		// overloads for binds 
		virtual void Bind(unsigned int slot = 0) const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual unsigned int  GetID() const = 0;
	};

	class KNIGHT_ENGINE_API Texture2D :public Texture {
	public:
		static Ref<Texture2D>Create(const std::string&filepath);

	};
}

// FOR TEXTURE CLASS I AM FOLLOWING SCERNO TO THE CORE IN OTHER I DO TRIED TO INVEST SOME THOUGHT BUT IT IS NEW 
// SO I MIGHT STRUGGLE 
