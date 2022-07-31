#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"

#include "Framework/Engine/Engine.h"
#include "Framework/Engine/Input/InputManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CBaseCamera::CBaseCamera(const CConfig& rConfig, const Vector3& position, const Vector3& defaultUp, const Vector3& defaultFwd, const Vector3& defaultRight, CInputManager& rInputManager)
	: m_DefaultUp(defaultUp)
	, m_DefaultForward(defaultFwd)
	, m_DefaultRight(defaultRight)
	, m_vPosition(position)
	, m_dirPress(static_cast<int>(eDir::COUNT), false)
{
	const float screenAspect = static_cast<float>(rConfig.GetScreenWidth()) / static_cast<float>(rConfig.GetScreenHeight());

	m_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(
		rConfig.GetFOV(),
		screenAspect,
		rConfig.GetScreenNear(),
		rConfig.GetScreenFar());

	XMVECTOR determinant = DirectX::XMMatrixDeterminant(m_projectionMatrix);
	m_invProjMatrix = XMMatrixInverse(&determinant, m_projectionMatrix);


    auto keyboardEventCbk = [this](const CKeyboardEvent& rKeyboardEvent) -> void {
        OnKeyboardEvent(rKeyboardEvent);
    };

    auto mouseEventCbk = [this](const CMouseEvent& rMouseEvent) -> void {
		OnMouseEvent(rMouseEvent);
    };

	m_KeyboardEventId = rInputManager.KeyboardEvent.Attach(keyboardEventCbk);
	m_MouseEventId = rInputManager.MouseEvent.Attach(mouseEventCbk);
}

CBaseCamera::~CBaseCamera()
{}

void CBaseCamera::Shutdown(CInputManager& rInputManager)
{
	rInputManager.KeyboardEvent.Detach(m_KeyboardEventId);
	rInputManager.MouseEvent.Detach(m_MouseEventId);
}

void CBaseCamera::UpdateKeyEvent(const CKeyboardEvent& rKeyboardEvent, const bool bEnableDir)
{
    eDir directionPress = eDir::COUNT;
    switch (rKeyboardEvent.GetKeyCode())
    {
    case CKeyboardEvent::KeyCodes::KEY_W:
        directionPress = eDir::FORWARD;
        break;
    case CKeyboardEvent::KeyCodes::KEY_S:
        directionPress = eDir::BACKWARDS;
        break;
    case CKeyboardEvent::KeyCodes::KEY_A:
        directionPress = eDir::LEFT;
        break;
    case CKeyboardEvent::KeyCodes::KEY_D:
        directionPress = eDir::RIGHT;
        break;
    case CKeyboardEvent::KeyCodes::KEY_E:
        directionPress = eDir::UP;
        break;
    case CKeyboardEvent::KeyCodes::KEY_Q:
        directionPress = eDir::DOWN;
        break;
    default:
        //is not an input we care about
        return;
    }

    m_dirPress[static_cast<int>(directionPress)] = bEnableDir;
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
