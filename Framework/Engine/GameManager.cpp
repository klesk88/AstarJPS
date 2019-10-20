#include "GameManager.h"

#include <algorithm>
#include <windows.h>

#include "entity/Entity.h"
#include "Engine.h"
#include "Core/Config.h"
#include "Input/InputManager.h"
#include "../Utils/DebugMacros.h"

CGameManager::CBatchCommands::CBatchCommands()
{
	m_Commands.reserve(100);
}

CGameManager::CBatchCommands::~CBatchCommands()
{}

void CGameManager::CBatchCommands::RunCommands()
{
	for (auto& command : m_Commands)
	{
		command();
	}
	m_Commands.clear();
}

//////////////////////////////////////////////////////////////////////////

CGameManager::CGameManager()
	: m_dUpdateTimeMs(0)
	, m_bDemoPaused(false)
{}


void CGameManager::Init(const CConfig& rConfig, CInputManager& rInputManager)
{
	m_dUpdateTimeMs = rConfig.GetGameUpdateTime();
	StartCounter();

	m_KeyboardEventId = rInputManager.KeyboardEvent.Attach([this](const CKeyboardEvent& rKeyboardEvent) { OnKeyboardEvent(rKeyboardEvent); });
}

void CGameManager::Shutdown()
{
	CEngine::GetInstance()->GetInputManager().KeyboardEvent.Detach(m_KeyboardEventId);
}

void CGameManager::Update()
{
	m_BatchCommands.RunCommands();

	UpdateTimer();
	if (m_bDemoPaused)
	{
		return;
	}

#if _DEBUG
	//we are debugging probably
	if (m_dDeltaTime > 200)
	{
		return;
	}
#endif

	for (CEntity* pEntity : m_entities)
	{
		pEntity->Update(m_dDeltaTime);
	}
}

void CGameManager::AddEntityToUpdate(CEntity& rEntity)
{
#if _DEBUG
	std::vector<CEntity*>::const_iterator iter = std::find(m_entities.begin(), m_entities.end(), &rEntity);
	ASSERT(iter == m_entities.end());
#endif

	CEntity* pEntityBatch = &rEntity;
	m_BatchCommands.PushCommand([=] { m_entities.push_back(pEntityBatch); });
}

void CGameManager::RemoveEntityFromUpdate(CEntity& rEntity)
{
	CEntity* pEntityBatch = &rEntity;

	m_BatchCommands.PushCommand([=] { 
		auto it = std::remove(m_entities.begin(), m_entities.end(), pEntityBatch);
		if (it != m_entities.end())
		{
			m_entities.erase(it);
		}
	});
}

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

