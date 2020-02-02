#include "GameManager.h"

#include <algorithm>
#include <windows.h>

#include "Engine.h"
#include "Core/Config.h"
#include "Input/InputManager.h"
#include "scene/SceneBase.h"
#include "../Utils/DebugMacros.h"

CGameManager::CGameManager()
	: m_dUpdateTimeMs(0)
	DEBUG_ONLY(, m_bDemoPaused(false))
{}

void CGameManager::Init(const CConfig& rConfig, CInputManager& rInputManager)
{
	m_dUpdateTimeMs = rConfig.GetGameUpdateTime();
	StartCounter();

#if _DEBUG
	m_KeyboardEventId = rInputManager.KeyboardEvent.Attach([this](const CKeyboardEvent& rKeyboardEvent) { OnKeyboardEvent(rKeyboardEvent); });
#endif
}

void CGameManager::Shutdown(CInputManager& rInputManager)
{
	DEBUG_ONLY(rInputManager.KeyboardEvent.Detach(m_KeyboardEventId);)
	m_scenes.clear();
}

void CGameManager::Update()
{
	UpdateTimer();

#if _DEBUG
	if (m_bDemoPaused)
	{
		return;
	}

	//we are debugging probably
	if (m_dDeltaTime > 200)
	{
		return;
	}
#endif

	for (std::unique_ptr<CSceneBase>& pScene : m_scenes)
	{
		pScene->Update(m_dDeltaTime);
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

void CGameManager::StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		ASSERT(false);

	m_ldInvFrequency = 1.0 / li.QuadPart;

	QueryPerformanceCounter(&li);
	m_uLastTime = li.QuadPart;
}

void CGameManager::UpdateTimer()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	unsigned __int64 elapsed = time.QuadPart - m_uLastTime;
	//transform in ms
	elapsed *= 1000;
	m_dDeltaTime = (double)(elapsed * m_ldInvFrequency);
	m_uLastTime = time.QuadPart;
}

#if _DEBUG

void CGameManager::OnKeyboardEvent(const CKeyboardEvent& rKeyboardEvent)
{
	switch (rKeyboardEvent.GetType())
	{
	case CKeyboardEvent::EventType::KEYDOWN:
		OnKeyDown(rKeyboardEvent);
		break;
	default:
		break;
	}
}

void CGameManager::OnKeyDown(const CKeyboardEvent& rKeyboardEvent)
{
	if (rKeyboardEvent.WasAlreadyPressed() || rKeyboardEvent.GetKeyCode() != CKeyboardEvent::KeyCodes::KEY_P)
	{
		return;
	}

	m_bDemoPaused = !m_bDemoPaused;
}

#endif

