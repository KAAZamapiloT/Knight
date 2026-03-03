#pragma once

#include"EngineApi.hpp"

#include"KnightEnginepch.h"
#include "Engine.hpp"
class KNIGHT_ENGINE_API	
Entity {

public:
	virtual uint64_t GetId()=0;
	virtual void SetId(uint64_t) = 0;
	virtual std::vector<uint64_t> GetChild()=0;
	
private:
	uint64_t id;
	std::vector<uint64_t> ChildrenId;

};


/* it is just a id and it will contaion components(data) and Sytems(logic) and these will change
the game in some way 
*/