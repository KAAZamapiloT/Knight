#pragma once
#include "EngineApi.hpp"
#ifdef KNIGHT_PLATFORM_WINDOWS
#include"Windows.h"
#endif // 
#include<stdlib.h>
#include"cstddef"
#include"vector"
#include<iostream>
#include "Core/Logger.hpp"
#include<string>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<queue>
#include<algorithm>
#include"cstdint"
#include<sstream>
#include<functional>
#include<memory>
#include<utility>
#include<stack>
#include<memory>
#include"Core/Core.h"
#define BIT(X) (1 << X)
#define KNIGHT_BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

