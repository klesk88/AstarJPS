#pragma once

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

//directx
#include <directxmath.h>

//simple config class which can is used to store base data
//which could be stored in a .ini file and be changed by the user
//and loaded at startup or once the game have been loaded

class CConfig
{
public:
	CConfig() = default;
	~CConfig() = default;

	void Load();

	[[nodiscard]] int GetScreenWidth() const;
	[[nodiscard]] int GetScreenHeight() const;
	[[nodiscard]] bool IsFullScreen() const;
	[[nodiscard]] bool GetVSyncEnable() const;
	[[nodiscard]] float GetScreenNear() const;
	[[nodiscard]] float GetScreenFar() const;
	[[nodiscard]] float GetFOV() const;
	[[nodiscard]] unsigned int GetGameUpdateTime() const;

private:
	int m_iScreenWidth = 1024;
	int m_iScreenHeight = 768;
	float m_fScreenNear = 0.01f;
	float m_fScreenFar = 100.f;
	float m_fFOV = DirectX::XM_PI / 4.0f;
	unsigned int m_uGameUpdateTimeMs = 1500;
	bool m_bFullScreen = false;
	bool m_bEnableVSync = false;
};

inline int CConfig::GetScreenWidth() const { return m_iScreenWidth; }
inline int CConfig::GetScreenHeight() const { return m_iScreenHeight; }
inline bool CConfig::IsFullScreen() const { return m_bFullScreen; }
inline bool CConfig::GetVSyncEnable() const { return m_bEnableVSync; }
inline float CConfig::GetScreenNear() const { return m_fScreenNear; }
inline float CConfig::GetScreenFar() const { return m_fScreenFar; }
inline float CConfig::GetFOV() const { return m_fFOV; }
inline unsigned int CConfig::GetGameUpdateTime() const { return m_uGameUpdateTimeMs; }