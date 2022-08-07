#pragma once

#include "Framework/Engine/Core/ConfigBase.h"
#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

//config file to load data for the window
class CWindowConfig final : public CConfigBase
{
public:
	CWindowConfig() = default;
	~CWindowConfig() = default;

	void Load() override;

	[[nodiscard]] int GetScreenWidth() const;
	[[nodiscard]] int GetScreenHeight() const;
	[[nodiscard]] bool IsFullScreen() const;
	[[nodiscard]] bool GetVSyncEnable() const;
	[[nodiscard]] float GetScreenNear() const;
	[[nodiscard]] float GetScreenFar() const;

private:
    float m_fScreenNear = 0.01f;
    float m_fScreenFar = 100.f;
	int m_iScreenWidth = 1024;
	int m_iScreenHeight = 768;
	bool m_bFullScreen = false;
	bool m_bEnableVSync = false;
};

inline int CWindowConfig::GetScreenWidth() const { return m_iScreenWidth; }
inline int CWindowConfig::GetScreenHeight() const { return m_iScreenHeight; }
inline bool CWindowConfig::IsFullScreen() const { return m_bFullScreen; }
inline bool CWindowConfig::GetVSyncEnable() const { return m_bEnableVSync; }
inline float CWindowConfig::GetScreenNear() const { return m_fScreenNear; }
inline float CWindowConfig::GetScreenFar() const { return m_fScreenFar; }
