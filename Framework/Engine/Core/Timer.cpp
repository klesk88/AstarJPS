#include "Timer.h"

#include <windows.h>
#include "../../Utils/DebugMacros.h"

void CTimer::Start()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		ASSERT(false);

	m_dPcFrequencyInverse = 1.0 / (double(li.QuadPart) / 1000.0);

	if(!QueryPerformanceCounter(&li))
		ASSERT(false);

	m_iLastTime = li.QuadPart;
}

void CTimer::Stop()
{
	ComputeDeltaTime();
}

void CTimer::ComputeDeltaTime()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceCounter(&li))
		ASSERT(false);

	m_dDeltaTime = (li.QuadPart - m_iLastTime) * m_dPcFrequencyInverse;
	m_iLastTime = li.QuadPart;
}

