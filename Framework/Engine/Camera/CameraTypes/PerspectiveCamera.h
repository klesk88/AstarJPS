#pragma once

#include <directxmath.h>
#include <windows.h>
#include <vector>

#include "BaseCamera.h"
#include "../../Core/Event.h"

class CConfig;
class CInputManager;
class CMouseEvent;
class CKeyboardEvent;

class CPerspectiveCamera final : public CBaseCamera
{
public:
	CPerspectiveCamera(const CConfig& rConfig, CInputManager& rInputManager);
	~CPerspectiveCamera();

	void Update() override;

private:
	void OnMouseEvent(const CMouseEvent& rMouseEvent) override;
	void OnRightMouseButtonPress(HWND hwnd);
	void OnRightMouseButtonRelease();
	void OnMouseMove(const CMouseEvent& rMouseEvent);

	void UpdateKeyEvent(const CKeyboardEvent& rKeyboardEvent, const bool bEnableDir) override;

private:
	const float m_fMovementSpeed;
	const float m_fRotationSpeed;
	float m_fPitch;
	float m_fYaw;
	float m_fRoll;
	int m_iWindowHeight;
	int m_iWindowWidth;
	bool m_bRightMouseBtnpress;
};