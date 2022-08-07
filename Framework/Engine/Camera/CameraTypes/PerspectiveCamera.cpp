#include "Framework/Engine/Camera/CameraTypes/PerspectiveCamera.h"

//framework
#include "Framework/Engine/Camera/Config/PerspectiveCameraConfig.h"
#include "Framework/Engine/Core/WindowConfig.h"
#include "Framework/Engine/Engine.h"
#include "Framework/Engine/Input/KeyboardMouse/Mouse/InputMouseState.h"
#include "Framework/Engine/Input/InputManager.h"
#include "Framework/Engine/ManagerUpdateInput.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CPerspectiveCamera::CPerspectiveCamera(const CWindowConfig& rWindowConfig, const CPerspectiveCameraConfig& rCameraConfig)
	: CBaseCamera(rWindowConfig, rCameraConfig, eCameraTye::PERSPECTIVE, Vector3(0.3f, 0.5f, -0.7f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.f, 0.f, 1.f), Vector3(1.0, 0.f, 0.f))
	, m_fAngularVelocityScale(rCameraConfig.GetAngularVelocityScale())
{
}

CPerspectiveCamera::~CPerspectiveCamera()
{}

void CPerspectiveCamera::Update(const CManagerUpdateInput& rInput)
{
	Vector3 offset;
	UpdatePositionOffset(rInput, offset);
	UpdatedRotation(rInput);

	const Matrix roll = DirectX::XMMatrixIdentity();
	const Matrix pitch = DirectX::XMMatrixRotationX(m_fPitch);
	const Matrix yaw = DirectX::XMMatrixRotationY(m_fYaw);

	const Matrix rotationMatrix = roll * pitch * yaw;

	const Vector3 up = Vector3::Transform(m_DefaultUp, rotationMatrix);
	const Vector3 forward = Vector3::Transform(m_DefaultForward, rotationMatrix);
	const Vector3 right = Vector3::Transform(m_DefaultRight, rotationMatrix);

	const Vector3 positionOffsetX(offset.x, offset.x, offset.x);
	const Vector3 positionOffsetZ(offset.z, offset.z, offset.z);
	const Vector3 positionOffsetY(offset.y, offset.y, offset.y);

	m_vPosition += positionOffsetX * right;
	m_vPosition += positionOffsetZ * forward;
	m_vPosition += positionOffsetY * up;

	static const Vector3 forwardOffset(10.f, 10.f, 10.f);
	const Vector3 lookAt = m_vPosition + (forward * forwardOffset);
	m_viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_vPosition), lookAt, up);
	m_invViewMatrix = XMMatrixInverse(nullptr, m_viewMatrix);
}

void CPerspectiveCamera::UpdatedRotation(const CManagerUpdateInput& rInput)
{
	const CInputMouseState& rMouseState = rInput.GetMouseState();
	if (!rMouseState.IsPressed(MouseKeyCodes::KeyCodes::RIGHT_BUTTON))
	{
		return;
	}

	if (!rMouseState.HasPositonDelta())
	{
		return;
	}

	const float XDeltaThisFrame = rMouseState.GetPosDeltaXThisFrame();
	const float YDeltaThisFrame = rMouseState.GetPosDeltaYThisFrame();

	const float fMaxAngularVelocity = DirectX::XM_PI * rInput.GetDeltaTime() * m_fAngularVelocityScale;
	m_fYaw += XDeltaThisFrame * fMaxAngularVelocity;
    m_fPitch += YDeltaThisFrame * fMaxAngularVelocity;

    //force the pitch to be constrained between -90 and 90 degrees

    if (m_fPitch > DirectX::XM_PIDIV2)
    {
        m_fPitch = DirectX::XM_PIDIV2;
    }
    else if (m_fPitch < -DirectX::XM_PIDIV2)
    {
        m_fPitch = -DirectX::XM_PIDIV2;
    }

    if (m_fYaw > DirectX::XM_2PI)
    {
        m_fYaw -= DirectX::XM_2PI;
    }
    else if (m_fYaw < -DirectX::XM_2PI)
    {
        m_fYaw += DirectX::XM_2PI;
    }
}
