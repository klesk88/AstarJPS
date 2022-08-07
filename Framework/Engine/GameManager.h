#pragma once

#include "Framework/Engine/Core/Event.h"
#include "Framework/Engine/Scene/SceneBase.h"
#include "Framework/Utils/ClassMacros.h"

//std
#include <functional>
#include <memory>
#include <vector>

class CConfig;
class CKeyboardEvent;
class CManagerUpdateInput;

//this class contains all the scenes currently running, or which will need to run
//if a scene is not needed anymore it will be remove
class CGameManager
{
public:
	CGameManager() = default;
	~CGameManager() = default;

	void Init(const CConfig& rConfig);
	void Shutdown();

	void Update(const CManagerUpdateInput& rInput);
	void AddScene(std::unique_ptr<CSceneBase> rScene);
	void RemoveScene(std::unique_ptr<CSceneBase>& rScene);

private:
	std::vector<std::unique_ptr<CSceneBase>> m_scenes;

#if _DEBUG
private:
	void DebugOnKeyDown(const CManagerUpdateInput& rInput);

private:
	CEventId m_DebugKeyboardEventId = CEventId::GetInvalidID();
	bool m_bDebugDemoPaused = false;
#endif
};
