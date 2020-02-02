#pragma once

//simple config class which can is used to store base data
//which could be stored in a .ini file and be changed by the user
//and loaded at startup or once the game have been loaded

class CConfig
{
public:
	CConfig();
	~CConfig();

	void Load();

	int GetScreenWidth() const { return m_iScreenWidth; }
	int GetScreenHeight() const { return m_iScreenHeight; }
	bool IsFullScreen() const { return m_bFullScreen; }
	bool GetVSyncEnable() const { return m_bEnableVSync; }
	float GetScreenNear() const { return m_fScreenNear; }
	float GetScreenFar() const { return m_fScreenFar; }
	float GetFOV() const { return m_fFOV; }
	unsigned int GetGameUpdateTime() const { return m_uGameUpdateTimeMs; }

private:
	int m_iScreenWidth;
	int m_iScreenHeight;
	float m_fScreenNear;
	float m_fScreenFar;
	float m_fFOV;
	unsigned int m_uGameUpdateTimeMs;
	bool m_bFullScreen;
	bool m_bEnableVSync;
};