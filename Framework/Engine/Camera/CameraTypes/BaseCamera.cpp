#include "BaseCamera.h"

#include <directxmath.h>

#include "../../Engine.h"
#include "../../Input/InputManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CBaseCamera::CBaseCamera(const CConfig& rConfig, const Vector3& position, const Vector3& defaultUp, const Vector3& defaultFwd, const Vector3& defaultRight, CInputManager& rInputManager)
	: m_projectionMatrix(DirectX::XMMatrixIdentity())
	, m_viewMatrix(DirectX::XMMatrixIdentity())
	, m_invViewMatrix(DirectX::XMMatrixIdentity())
	, m_vPosition(position)
	, m_DefaultUp(defaultUp)
	, m_DefaultForward(defaultFwd)
	, m_DefaultRight(defaultRight)
	, m_bIsActive(false)
	, m_fMovementSpeed(0.001f)
{
	const float screenAspect = (float)rConfig.GetScreenWidth() / (float)rConfig.GetScreenHeight();

	m_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(
		rConfig.GetFOV(),
		screenAspect,
		rConfig.GetScreenNear(),
		rConfig.GetScreenFar());

	XMVECTOR determinant = DirectX::XMMatrixDeterminant(m_projectionMatrix);
	m_invProjMatrix = XMMatrixInverse(&determinant, m_projectionMatrix);

	m_dirPress.resize((int)eDir::COUNT, false);

	m_KeyboardEventId = rInputManager.KeyboardEvent.Attach([this](const CKeyboardEvent& rKeyboardEvent) { OnKeyboardEvent(rKeyboardEvent); });
	m_MouseEventId = rInputManager.MouseEvent.Attach([this](const CMouseEvent& rMouseEvent) { OnMouseEvent(rMouseEvent); });
}

CBaseCamera::~CBaseCamera()
{}

void CBaseCamera::Shutdown(CInputManager& rInputManager)
{
	rInputManager.KeyboardEvent.Detach(m_KeyboardEventId);
	rInputManager.MouseEvent.Detach(m_MouseEventId);
}

void CBaseCamera::OnKeyboardEvent(const CKeyboardEvent& rKeyboardEvent)
{
	if (!IsActive())
	{
		return;
	}

	switch (rKeyboardEvent.GetType())
	{
	case CKeyboardEvent::EventType::KEYUP:
		OnKeyUp(rKeyboardEvent);
		break;
	case CKeyboardEvent::EventType::KEYDOWN:
		OnKeyDown(rKeyboardEvent);
		break;
	default:
		break;
	}
}

void CBaseCamera::OnKeyUp(const CKeyboardEvent& rKeyboardEvent)
{
	UpdateKeyEvent(rKeyboardEvent, false);
}

void CBaseCamera::OnKeyDown(const CKeyboardEvent& rKeyboardEvent)
{
	UpdateKeyEvent(rKeyboardEvent, true);
}

void CBaseCamera::UpdatePositionOffset(DirectX::SimpleMath::Vector3& rOutOffset)
{
	const Vector3 movementSpeed(m_fMovementSpeed, m_fMovementSpeed, m_fMovementSpeed);
	rOutOffset = Vector3(0.f, 0.f, 0.f);

	for (int i = 0; i < m_dirPress.size(); ++i)
	{
		const bool bInputPress = m_dirPress[i];
		if (!bInputPress)
		{
			continue;
		}

		switch ((eDir)i)
		{
		case eDir::UP:
			rOutOffset += movementSpeed * m_DefaultUp;
			break;
		case eDir::DOWN:
			rOutOffset -= movementSpeed * m_DefaultUp;
			break;
		case eDir::LEFT:
			rOutOffset -= movementSpeed * m_DefaultRight;
			break;
		case eDir::RIGHT:
			rOutOffset += movementSpeed * m_DefaultRight;
			break;
		case eDir::FORWARD:
			rOutOffset += movementSpeed * m_DefaultForward;
			break;
		case eDir::BACKWARDS:
			rOutOffset -= movementSpeed * m_DefaultForward;
			break;
		}
	}
}
