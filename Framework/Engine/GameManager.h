#pragma once

//this class contains all the scenes currently running, or which will need to run
//if a scene is not needed anymore it will be remove

#include <functional>
#include <memory>
#include <vector>

#include "Core/Event.h"
#include "../Utils/ClassMacros.h"
#include "Scene/SceneBase.h"

class CConfig;
class CInputManager;
class CKeyboardEvent;

class CGameManager
{
public:
	CGameManager();

	void Init(const CConfig& rConfig, CInputManager& rInputManager);
	void Shutdown(CInputManager& rInputManager);

	void Update();
	void AddScene(std::unique_ptr<CSceneBase> rScene);
	void RemoveScene(std::unique_ptr<CSceneBase>& rScene);
	double GetDeltaTime() const { return m_dDeltaTime; }

private:

	void StartCounter();
	void UpdateTimer();

private:
	std::vector<std::unique_ptr<CSceneBase>> m_scenes;
	long double m_ldInvFrequency;
	unsigned __int64 m_uLastTime;
	double m_dDeltaTime;
	double m_dUpdateTimeMs;

#if _DEBUG
private:
	void OnKeyboardEvent(const CKeyboardEvent& rKeyboardEvent);
	void OnKeyDown(const CKeyboardEvent& rKeyboardEvent);

private:
	CEventId m_KeyboardEventId;
	bool m_bDemoPaused : 1;
#endif
};