#pragma once

//this class is responsible for keep track of the delta time between updated and call
//the update on the entities passing the current delta time

#include <functional>
#include <vector>

#include "Core/Event.h"
#include "../Utils/ClassMacros.h"

class CConfig;
class CInputManager;
class CKeyboardEvent;
class CSceneBase;

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
	void Shutdown(CInputManager& rInputManager);

	void Update();
	void AddScene(CSceneBase& rScene);
	void RemoveScene(CSceneBase& rScene);
	double GetDeltaTime() const { return m_dDeltaTime; }

private:
	void StartCounter();
	void UpdateTimer();

private:
	CBatchCommands m_BatchCommands;
	std::vector<CSceneBase*> m_scenes;
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