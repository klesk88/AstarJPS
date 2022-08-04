#pragma once

#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"
#include "Framework/Engine/Core/Event.h"

class CConfig;
class CInputManager;

class CTopDownCamera final : public CBaseCamera
{
public:
	explicit CTopDownCamera(const CConfig& rConfig, CInputManager& rInputManager);
	~CTopDownCamera();

	//CBaseCamera
	void Update(const float fDeltaTime) override;
	//CBaseCamera

private:
	//CBaseCamera
	void OnMouseEvent(const CMouseEvent& rMouseEvent) override;
	void UpdatePositionOffset(const float fDeltaTimeSec, DirectX::SimpleMath::Vector3& rOutOffset) override;
	//CBaseCamera

private:
	DirectX::SimpleMath::Matrix m_OrthoMatrix = DirectX::XMMatrixIdentity();
	DirectX::SimpleMath::Matrix m_InvOrthoMatrix = DirectX::XMMatrixIdentity();
	const float m_fWheelScale = 0.01f;
	const float m_fStartScale = 0.05f;
	float m_fMouseWheelDelta = 0.f;
};