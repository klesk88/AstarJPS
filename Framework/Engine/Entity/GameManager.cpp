#include "EntityManager.h"

#include <algorithm>
#include <windows.h>

#include "Entity.h"
#include "../Engine.h"
#include "../Core/Config.h"
#include "../Input/InputManager.h"
#include "../../Utils/DebugMacros.h"

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
	: m_UpdateTimeMs(0)
	, m_iLastTimeUpdated(0)
	, m_bDemoPaused(false)
{}


void CGameManager::Init(const CConfig& rConfig, CInputManager& rInputManager)
{
	m_UpdateTimeMs = rConfig.GetGameUpdateTime();
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

	const bool bIsTimeToUpdate = UpdateTimeGetIfUpdate();
	if (m_bDemoPaused || !bIsTimeToUpdate)
	{
		return;
	}

	for (CEntity* pEntity : m_entities)
	{
		pEntity->Update();
	}
}

void CGameManager::AddEntityToUpdate(CEntity& rEntity)
{
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
	case CKeyboardEvent::KEYDOWN:
		OnKeyDown(rKeyboardEvent);
		break;
	default:
		break;
	}
}

void CGameManager::OnKeyDown(const CKeyboardEvent& rKeyboardEvent)
{
	if (rKeyboardEvent.WasAlreadyPressed() || rKeyboardEvent.GetKeyCode() != CKeyboardEvent::KEY_P)
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

	m_dPcFrequencyInverse = 1.0 / (double(li.QuadPart) / 1000.0);

	QueryPerformanceCounter(&li);
	m_iLastTime = li.QuadPart;
}

bool CGameManager::UpdateTimeGetIfUpdate()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	m_dDeltaTime = (li.QuadPart - m_iLastTime) * m_dPcFrequencyInverse;
	m_iLastTime = li.QuadPart;
	const bool bUpdate = ((li.QuadPart - m_iLastTimeUpdated) * m_dPcFrequencyInverse) > m_UpdateTimeMs;
	if (bUpdate)
	{
		m_iLastTimeUpdated = m_iLastTime;
	}

	return bUpdate;
}

