#pragma once

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
private:
	enum class eCameraTye : char
	{
		PERSPECTIVE = 0,
		TOP_DOWN,

		COUNT
	};

public:
	CCameraManager() = default;
	~CCameraManager();

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
	CEventId m_keyboardEventId = CEventId::GetInvalidID();
	eCameraTye m_activeCameraType = eCameraTye::TOP_DOWN;
};

inline const CBaseCamera& CCameraManager::GetCurrentCamera() const { return *m_cameras[static_cast<unsigned int>(m_activeCameraType)]; }