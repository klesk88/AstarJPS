#include "Framework/Engine/GameManager.h"

#include "Framework/Engine/Core/Config.h"
#include "Framework/Engine/Engine.h"
#include "Framework/Engine/Input/InputManager.h"
#include "Framework/Engine/ManagerUpdateInput.h"
#include "Framework/Engine/Scene/SceneBase.h"
#include "Framework/Utils/DebugMacros.h"

//windows
#include <windows.h>

//std
#include <algorithm>

#if _DEBUG
#include "Framework/Engine/Input/KeyboardMouse/Keyboard/InputKeyboardState.h"
#endif

void CGameManager::Init(const CConfig& rConfig)
{
}

void CGameManager::Shutdown()
{
	m_scenes.clear();
}

void CGameManager::Update(const CManagerUpdateInput& rInput)
{
#if _DEBUG
	DebugOnKeyDown(rInput);
	if (m_bDebugDemoPaused)
	{
		return;
	}
#endif

	for (std::unique_ptr<CSceneBase>& pScene : m_scenes)
	{
		pScene->Update(rInput.GetDeltaTime());
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

void CGameManager::DebugOnKeyDown(const CManagerUpdateInput& rInput)
{
	const CInputKeyboardState& rKeyboardState = rInput.GetKeyboardState();
	if (rKeyboardState.WasPressed(KeyboardKeyCodes::KeyCodes::KEY_P))
	{
		m_bDebugDemoPaused = !m_bDebugDemoPaused;
	}
}

#endif

