#pragma once

#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"
#include "Framework/Engine/Core/Event.h"

//directx
#include <directxmath.h>

class CManagerUpdateInput;
class CPerspectiveCameraConfig;
class CWindowConfig;

class CPerspectiveCamera final : public CBaseCamera
{
public:
	explicit CPerspectiveCamera(const CWindowConfig& rConfig, const CPerspectiveCameraConfig& rCameraConfig);
	~CPerspectiveCamera();

	//CBaseCamera
	void Update(const CManagerUpdateInput& rInput) override;
	//CBaseCamera

private:
	void UpdatedRotation(const CManagerUpdateInput& rInput);

private:
	float m_fPitch = 0.f;
	float m_fYaw = 0.f;
	float m_fRoll = 0.f;
	const float m_fAngularVelocityScale = 1.f;
};