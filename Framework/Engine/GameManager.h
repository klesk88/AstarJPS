#pragma once

//this class is responsible for keep track of the delta time between updated and call
//the update on the entities passing the current delta time

#include <functional>
#include <vector>

#include "Core/Event.h"
#include "../Utils/ClassMacros.h"

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
	void UpdateTimer();

private:
	CBatchCommands m_BatchCommands;
	CEventId m_KeyboardEventId;
	std::vector<CEntity*> m_entities;
	long double m_ldInvFrequency;
	unsigned __int64 m_uLastTime;
	double m_dDeltaTime;
	double m_dUpdateTimeMs;
	bool m_bDemoPaused : 1;
};