#pragma once

#ifdef _DEBUG
#include <cassert>
#endif

#ifdef _DEBUG
#define ASSERT(x) assert(x) 
#define DEBUG_ONLY(...) __VA_ARGS__
#else
#define ASSERT(x)  do {} while (false)
#define DEBUG_ONLY(...)
#endif