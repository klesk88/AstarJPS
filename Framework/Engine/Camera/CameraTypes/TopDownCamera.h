#pragma once

#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"
#include "Framework/Engine/Core/Event.h"

class CManagerUpdateInput;
class CTopDownCameraConfig;
class CWindowConfig;

class CTopDownCamera final : public CBaseCamera
{
public:
	explicit CTopDownCamera(const CWindowConfig& rWindowConfig, const CTopDownCameraConfig& rCameraConfig);
	~CTopDownCamera() = default;

	//CBaseCamera
	void Update(const CManagerUpdateInput& rInput) override;
	//CBaseCamera

private:
	void UpdateMouseWheel(const CManagerUpdateInput& rInput, DirectX::SimpleMath::Vector3& rOutPosition);

private:
	DirectX::SimpleMath::Matrix m_OrthoMatrix = DirectX::XMMatrixIdentity();
	DirectX::SimpleMath::Matrix m_InvOrthoMatrix = DirectX::XMMatrixIdentity();
	float m_fWheelScale = 0.f;
};