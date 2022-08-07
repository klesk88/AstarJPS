#include "Framework/Engine/Core/Timer.h"

//std
#include <chrono>

CScopedTimer::CScopedTimer(float& rfOutTimeMs)
    : m_fOutTimeMs(rfOutTimeMs)
{
    const auto time = std::chrono::high_resolution_clock::now();
    m_uStartTimeNs = time.time_since_epoch().count();
}

CScopedTimer::~CScopedTimer()
{
    const uint64_t uTimeValue = ComputeDeltaTimeNanoSeconds();

    //now convert time obtained in ms
    const auto duration = std::chrono::duration<uint64_t, std::chrono::steady_clock::period>(uTimeValue);
    const uint64_t uNumMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    static constexpr float fTimeToMs = 1.f / 1000.f;
    m_fOutTimeMs = static_cast<float>(uNumMicroseconds) * fTimeToMs;
}

uint64_t CScopedTimer::ComputeDeltaTimeNanoSeconds() const
{
    const auto time = std::chrono::high_resolution_clock::now();
    const uint64_t uCurrentTime = time.time_since_epoch().count();
    const uint64_t uDiff = uCurrentTime - m_uStartTimeNs;
    return uDiff;
}
