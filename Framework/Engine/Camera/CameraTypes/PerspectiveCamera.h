#pragma once

#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"
#include "Framework/Engine/Core/Event.h"

//directx
#include <directxmath.h>

//std
#include <vector>

class CConfig;
class CInputManager;
class CMouseEvent;
class CKeyboardEvent;

class CPerspectiveCamera final : public CBaseCamera
{
public:
	explicit CPerspectiveCamera(const CConfig& rConfig, CInputManager& rInputManager);
	~CPerspectiveCamera();

	//CBaseCamera
	void Update(const float fDeltaTimeSec) override;
	//CBaseCamera

private:
	//CBaseCamera
	void OnMouseEvent(const CMouseEvent& rMouseEvent) override;
	//CBaseCamera

	void OnRightMouseButtonPress(HWND hwnd);
	void OnRightMouseButtonRelease();
	void OnMouseMove(const CMouseEvent& rMouseEvent);

	void UpdatedRotation(const float fDeltaTimeSec);

private:
	float m_fPitch = 0.f;
	float m_fYaw = 0.f;
	float m_fRoll = 0.f;
	int m_iWindowHeight = 0;
	int m_iWindowWidth = 0;
	int m_iMouseDiffX = 0;
	int m_iMouseDiffY = 0;
	bool m_bRightMouseBtnpress = false;
};