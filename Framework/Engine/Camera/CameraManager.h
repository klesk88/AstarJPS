#pragma once

#include <vector>

#include "../Core/Event.h"
#include "../Core/SimpleMath.h"

class CBaseCamera;
class CConfig;
class CInputManager;
class CKeyboardEvent;

class CCameraManager
{
private:
	enum eCameraTye : char
	{
		PERSPECTIVE = 0,
		TOP_DOWN,

		COUNT
	};

public:
	CCameraManager();
	~CCameraManager();

	void Init(const CConfig& rConfig, CInputManager& rInputManager);
	void Shutdown(CInputManager& rInputManager);

	void Update();

	const CBaseCamera& GetCurrentCamera() const { return *m_cameras[(int)m_activeCameraType]; }

private:
	void OnKeyboardEvent(const CKeyboardEvent& rKeyboardEvent);
	void OnKeyDown(const CKeyboardEvent& rKeyboardEvent);

private:
	std::vector<CBaseCamera*> m_cameras;
	CEventId m_keyboardEventId;
	eCameraTye m_activeCameraType;
};