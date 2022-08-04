#pragma once

#include "Framework/Utils/ClassMacros.h"
#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

//std
#include <type_traits> //this is for uint64_t

//a scoped timer that stored in the input variable the resulting time taken in milliseconds
//inside the score in which CScopedTimer is declared, 
class CScopedTimer
{
	NON_COPYABLE_CLASS(CScopedTimer)

public:
	explicit CScopedTimer(float& rfOutTimeMs);
	~CScopedTimer();

private:
	[[nodiscard]] uint64_t ComputeDeltaTimeNanoSeconds() const;

private:
	//start time in nanoseconds
	uint64_t m_uStartTimeNs = 0;
	float& m_fOutTimeMs;
};
