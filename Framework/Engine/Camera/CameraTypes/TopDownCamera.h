#pragma once

#include <directxmath.h>

#include "BaseCamera.h"
#include "../../Core/Event.h"

class CConfig;
class CInputManager;

class CTopDownCamera final : public CBaseCamera
{
public:
	CTopDownCamera(const CConfig& rConfig, CInputManager& rInputManager);
	~CTopDownCamera();

	void Update() override;

private:
	void UpdateKeyEvent(const CKeyboardEvent& rKeyboardEvent, const bool bEnableDir) override;

	void OnMouseEvent(const CMouseEvent& rMouseEvent) override;
	void UpdatePositionOffset(DirectX::SimpleMath::Vector3& rOutOffset) override;

private:
	DirectX::SimpleMath::Matrix m_OrthoMatrix;
	DirectX::SimpleMath::Matrix m_InvOrthoMatrix;
	const float m_fWheelScale;
	const float m_fStartScale;
	float m_fMouseWheelDelta;
};