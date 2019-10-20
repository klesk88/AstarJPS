#pragma once

#include <functional>
#include <list>
#include <vector>

#include "../Core/Event.h"
#include "../../Utils/ClassMacros.h"

class CConfig;
class CEntity;
class CInputManager;
class CKeyboardEvent;

class CGameManager
{
private:
	class CBatchCommands
	{
		NON_COPYABLE_CLASS(CBatchCommands)

	public:
		using Command = std::function<void()>;

		CBatchCommands();
		~CBatchCommands();

		template<typename T>
		void PushCommand(T&& command) { m_Commands.emplace_back(std::forward<T>(command)); }

		void RunCommands();

	private:
		std::vector<Command> m_Commands;
	};

public:
	CGameManager();

	void Init(const CConfig& rConfig, CInputManager& rInputManager);
	void Shutdown();

	void Update();
	void AddEntityToUpdate(CEntity& rEntity);
	void RemoveEntityFromUpdate(CEntity& rEntity);
	double GetDeltaTime() const { return m_dDeltaTime; }

private:
	void OnKeyboardEvent(const CKeyboardEvent& rKeyboardEvent);
	void OnKeyDown(const CKeyboardEvent& rKeyboardEvent);
	void StartCounter();
	bool UpdateTimeGetIfUpdate();

private:
	CBatchCommands m_BatchCommands;
	CEventId m_KeyboardEventId;
	std::list<CEntity*> m_entities;
	double m_dPcFrequencyInverse;
	__int64 m_iLastTime;
	double m_dDeltaTime;
	double m_UpdateTimeMs;
	__int64 m_iLastTimeUpdated;
	bool m_bDemoPaused : 1;
};