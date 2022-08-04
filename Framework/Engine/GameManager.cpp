#include "Framework/Engine/GameManager.h"

#include "Framework/Engine/Core/Config.h"
#include "Framework/Engine/Engine.h"
#include "Framework/Engine/Input/InputManager.h"
#include "Framework/Engine/Scene/SceneBase.h"
#include "Framework/Utils/DebugMacros.h"

//windows
#include <windows.h>

//std
#include <algorithm>

void CGameManager::Init(const CConfig& rConfig, CInputManager& rInputManager)
{
#if _DEBUG
	auto KeyboardEventCbk = [this](const CKeyboardEvent& rKeyboardEvent) -> void {
		DebugOnKeyboardEvent(rKeyboardEvent);
	};

	m_DebugKeyboardEventId = rInputManager.KeyboardEvent.Attach(KeyboardEventCbk);
#endif
}

void CGameManager::Shutdown(CInputManager& rInputManager)
{
	DEBUG_ONLY(rInputManager.KeyboardEvent.Detach(m_DebugKeyboardEventId);)
	m_scenes.clear();
}

void CGameManager::Update(const float fDeltaTimeSec)
{
#if _DEBUG
	if (m_bDebugDemoPaused)
	{
		return;
	}
#endif

	for (std::unique_ptr<CSceneBase>& pScene : m_scenes)
	{
		pScene->Update(fDeltaTimeSec);
	}
}

void CGameManager::AddScene(std::unique_ptr<CSceneBase> rScene)
{
#if _DEBUG
	std::vector<std::unique_ptr<CSceneBase>>::const_iterator iter = std::find(m_scenes.begin(), m_scenes.end(), rScene);
	ASSERT(iter == m_scenes.end());
#endif

	rScene->Init();
	m_scenes.push_back(std::move(rScene));
}

void CGameManager::RemoveScene(std::unique_ptr<CSceneBase>& rScene)
{
	auto it = std::remove(m_scenes.begin(), m_scenes.end(), rScene);
	if (it != m_scenes.end())
	{
		m_scenes.erase(it);
	}
}

#if _DEBUG

void CGameManager::DebugOnKeyboardEvent(const CKeyboardEvent& rKeyboardEvent)
{
	switch (rKeyboardEvent.GetType())
	{
	case CKeyboardEvent::EventType::KEYDOWN:
		DebugOnKeyDown(rKeyboardEvent);
		break;
	default:
		break;
	}
}

void CGameManager::DebugOnKeyDown(const CKeyboardEvent& rKeyboardEvent)
{
	if (rKeyboardEvent.WasAlreadyPressed() || rKeyboardEvent.GetKeyCode() != CKeyboardEvent::KeyCodes::KEY_P)
	{
		return;
	}

	m_bDebugDemoPaused = !m_bDebugDemoPaused;
}

#endif

