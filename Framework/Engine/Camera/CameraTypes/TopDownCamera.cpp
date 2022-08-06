#include "Framework/Engine/Camera/CameraTypes/TopDownCamera.h"

//framework
#include "Framework/Engine/Camera/Config/TopDownCameraConfig.h"
#include "Framework/Engine/Core/WindowConfig.h"
#include "Framework/Engine/Input/InputManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CTopDownCamera::CTopDownCamera(const CWindowConfig& rWindowConfig, const CTopDownCameraConfig& rCameraConfig, CInputManager& rInputManager)
	: CBaseCamera(rWindowConfig, rCameraConfig, eCameraTye::TOP_DOWN, Vector3(5.15f, 13.f, 5.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.f, 0.f, 1.f), Vector3(1.0, 0.f, 0.f), rInputManager)
{
	const float fAspect = static_cast<float>(rWindowConfig.GetScreenWidth()) / static_cast<float>(rWindowConfig.GetScreenHeight());

	m_OrthoMatrix = DirectX::XMMatrixOrthographicLH(
		6.0f * fAspect,
		6.0f,
		rWindowConfig.GetScreenNear(),
		rWindowConfig.GetScreenFar());

	XMVECTOR determinant = DirectX::XMMatrixDeterminant(m_OrthoMatrix);
	m_InvOrthoMatrix = XMMatrixInverse(&determinant, m_OrthoMatrix);

	m_fMouseWheelDelta = rCameraConfig.GetWheelDelta();
	m_fWheelScale = rCameraConfig.GetWheelScale();
}

CTopDownCamera::~CTopDownCamera()
{}

void CTopDownCamera::Update(const float fDeltaTimeSec)
{
	Vector3 offset;
	UpdatePositionOffset(fDeltaTimeSec, offset);
	m_vPosition += offset;

	const Matrix pitch = DirectX::XMMatrixRotationX(DirectX::XM_PIDIV2);
	const Matrix rotationMatrix = pitch;

	const Vector3 up = Vector3::Transform(m_DefaultUp, rotationMatrix);
	const Vector3 forward = Vector3::Transform(m_DefaultForward, rotationMatrix);
	const Vector3 right = Vector3::Transform(m_DefaultRight, rotationMatrix);

	static const Vector3 forwardOffset(10.f, 10.f, 10.f);
	const Vector3 lookAt = m_vPosition + (forward * forwardOffset);
	m_viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&m_vPosition), lookAt, up);
	m_invViewMatrix = XMMatrixInverse(nullptr, m_viewMatrix);
}

void CTopDownCamera::OnMouseEvent(const CMouseEvent& rMouseEvent)
{
	if (!IsActive())
	{
		return;
	}

	switch (rMouseEvent.GetEventType())
	{
	case CMouseEvent::MOUSE_WHEEL:
		m_fMouseWheelDelta = rMouseEvent.GetWheelDelta();
		break;
	default:
		break;
	}
}

void CTopDownCamera::UpdatePositionOffset(const float fDeltaTimeSec, Vector3& rOutOffset)
{
	CBaseCamera::UpdatePositionOffset(fDeltaTimeSec, rOutOffset);

	if (m_fMouseWheelDelta == 0.f)
	{
		return;
	}

	const float fWheelSpeedScaled = m_fWheelScale * m_fMouseWheelDelta;
	rOutOffset -= fWheelSpeedScaled * m_DefaultUp;
	m_fMouseWheelDelta = 0.f;
}
