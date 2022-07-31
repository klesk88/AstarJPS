#pragma once

#include "Framework/Engine/Core/Event.h"
#include "Framework/Engine/Scene/SceneBase.h"
#include "Framework/Utils/ClassMacros.h"

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

//std
#include <functional>
#include <memory>
#include <vector>

class CConfig;
class CInputManager;
class CKeyboardEvent;

//this class contains all the scenes currently running, or which will need to run
//if a scene is not needed anymore it will be remove
class CGameManager
{
public:
	CGameManager() = default;
	~CGameManager() = default;

	void Init(const CConfig& rConfig, CInputManager& rInputManager);
	void Shutdown(CInputManager& rInputManager);

	void Update();
	void AddScene(std::unique_ptr<CSceneBase> rScene);
	void RemoveScene(std::unique_ptr<CSceneBase>& rScene);
	[[nodiscard]] double GetDeltaTime() const;

private:
	void StartCounter();
	void UpdateTimer();

private:
	std::vector<std::unique_ptr<CSceneBase>> m_scenes;
	long double m_ldInvFrequency = 0.f;
	unsigned __int64 m_uLastTime = 0;
	double m_dDeltaTime = 0.0;
	double m_dUpdateTimeMs = 0.0;

#if _DEBUG
private:
	void DebugOnKeyboardEvent(const CKeyboardEvent& rKeyboardEvent);
	void DebugOnKeyDown(const CKeyboardEvent& rKeyboardEvent);

private:
	CEventId m_DebugKeyboardEventId = CEventId::GetInvalidID();
	bool m_bDebugDemoPaused = false;
#endif
};

inline double CGameManager::GetDeltaTime() const { return m_dDeltaTime; }