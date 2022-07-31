#include "Framework/Engine/Camera/CameraTypes/TopDownCamera.h"

#include "Framework/Engine/Core/Config.h"
#include "Framework/Engine/Input/InputManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CTopDownCamera::CTopDownCamera(const CConfig& rConfig, CInputManager& rInputManager)
	: CBaseCamera(rConfig, Vector3(5.15f, 13.f, 5.0f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.f, 0.f, 1.f), Vector3(1.0, 0.f, 0.f), rInputManager)
{
	const float fAspect = (float)rConfig.GetScreenWidth() / (float)rConfig.GetScreenHeight();

	m_OrthoMatrix = DirectX::XMMatrixOrthographicLH(
		6.0f * fAspect,
		6.0f,
		rConfig.GetScreenNear(),
		rConfig.GetScreenFar());

	XMVECTOR determinant = DirectX::XMMatrixDeterminant(m_OrthoMatrix);
	m_InvOrthoMatrix = XMMatrixInverse(&determinant, m_OrthoMatrix);
}

CTopDownCamera::~CTopDownCamera()
{}

void CTopDownCamera::Update()
{
	Vector3 offset;
	UpdatePositionOffset(offset);
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

void CTopDownCamera::UpdatePositionOffset(Vector3& rOutOffset)
{
	CBaseCamera::UpdatePositionOffset(rOutOffset);

	if (m_fMouseWheelDelta == 0.f)
	{
		return;
	}

	const float fWheelSpeedScaled = m_fWheelScale * m_fMouseWheelDelta;
	rOutOffset -= fWheelSpeedScaled * m_DefaultUp;
	m_fMouseWheelDelta = 0.f;
}
