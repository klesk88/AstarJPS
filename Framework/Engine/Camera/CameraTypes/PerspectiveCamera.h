#pragma once

#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"
#include "Framework/Engine/Core/Event.h"

//directx
#include <directxmath.h>

class CInputManager;
class CKeyboardEvent;
class CMouseEvent;
class CPerspectiveCameraConfig;
class CWindowConfig;

class CPerspectiveCamera final : public CBaseCamera
{
public:
	explicit CPerspectiveCamera(const CWindowConfig& rConfig, const CPerspectiveCameraConfig& rCameraConfig, CInputManager& rInputManager);
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
	float m_iMouseDiffX = 0.f;
	float m_iMouseDiffY = 0.g;
	bool m_bRightMouseBtnpress = false;
};