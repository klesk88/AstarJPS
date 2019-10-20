#pragma once

class CTimer
{
public:
	CTimer() = default;

	void Start();
	void Stop();

	double GetDeltaTime() const { return m_dDeltaTime; }

private:
	void ComputeDeltaTime();

private:
	unsigned __int64 m_iLastTime;
	float m_fPrecision;
	double m_dPcFrequencyInverse;
	double m_dDeltaTime;
};