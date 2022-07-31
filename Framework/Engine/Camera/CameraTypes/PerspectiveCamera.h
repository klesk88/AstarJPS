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
	void Update() override;
	//CBaseCamera

private:
	//CBaseCamera
	void OnMouseEvent(const CMouseEvent& rMouseEvent) override;
	//CBaseCamera

	void OnRightMouseButtonPress(HWND hwnd);
	void OnRightMouseButtonRelease();
	void OnMouseMove(const CMouseEvent& rMouseEvent);

private:
	const float m_fMovementSpeed = 0.001f;
	const float m_fRotationSpeed = 0.1f;
	float m_fPitch = 0.f;
	float m_fYaw = 0.f;
	float m_fRoll = 0.f;
	int m_iWindowHeight = 0;
	int m_iWindowWidth = 0;
	bool m_bRightMouseBtnpress = false;
};