#pragma once

#include "Framework/Engine/Camera/CameraTypes/CameraTypes.h"
#include "Framework/Engine/Core/Event.h"
#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

//std
#include <memory>
#include <vector>

class CBaseCamera;
class CConfig;
class CInputManager;
class CKeyboardEvent;

class CCameraManager
{
public:
	CCameraManager() = default;
	~CCameraManager();

	//would be better to dont pass in the input manager and have the engine update the input and then pass 
	//the current changes as an input struct to the cameras. However for this kind of demo this should be ok
	void Init(const CConfig& rConfig, CInputManager& rInputManager);
	void Shutdown(CInputManager& rInputManager);

	void Update(const float fDeltaTimeSec);

	//get the instance of the current selected camera by the user
	[[nodiscard]] const CBaseCamera& GetCurrentCamera() const;

private:
	//change the type of camera base on the user selection
	void OnKeyboardEvent(const CKeyboardEvent& rKeyboardEvent);
	void OnKeyDown(const CKeyboardEvent& rKeyboardEvent);

private:
	std::vector<std::unique_ptr<CBaseCamera>> m_cameras;
	CBaseCamera* m_pCurrentCamera = nullptr;
	CEventId m_keyboardEventId = CEventId::GetInvalidID();
};

inline const CBaseCamera& CCameraManager::GetCurrentCamera() const { return *m_pCurrentCamera; }