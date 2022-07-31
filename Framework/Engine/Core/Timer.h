#pragma once

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

class CTimer
{
public:
	CTimer() = default;
	~CTimer() = default;

	void Start();
	void Stop();

	[[nodiscard]] double GetDeltaTime() const;

private:
	void ComputeDeltaTime();

private:
	unsigned __int64 m_iLastTime = 0;
	double m_dPcFrequencyInverse = 0.0;
	double m_dDeltaTime = 0.0;
};

inline double CTimer::GetDeltaTime() const { return m_dDeltaTime; }