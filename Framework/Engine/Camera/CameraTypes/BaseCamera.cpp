#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"

//framework
#include "Framework/Engine/Camera/Config/CameraConfigBase.h"
#include "Framework/Engine/Core/WindowConfig.h"
#include "Framework/Engine/Engine.h"
#include "Framework/Engine/Input/InputManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CBaseCamera::CBaseCamera(const CWindowConfig& rWindowConfig, const CCameraConfigBase& rCameraConfig, const eCameraTye cameraType, const Vector3& rPosition, const Vector3& rDefaultUp, const Vector3& rDefaultFwd, const Vector3& rDefaultRight, CInputManager& rInputManager)
	: m_DefaultUp(rDefaultUp)
	, m_DefaultForward(rDefaultFwd)
	, m_DefaultRight(rDefaultRight)
	, m_vPosition(rPosition)
	, m_fMovementSpeed(rCameraConfig.GetMovementSpeed())
	, m_dirPress(static_cast<int>(eDir::COUNT), false)
	, m_CameraType(cameraType)
{
	const float screenAspect = static_cast<float>(rWindowConfig.GetScreenWidth()) / static_cast<float>(rWindowConfig.GetScreenHeight());

	m_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(
		rCameraConfig.GetFOV(),
		screenAspect,
		rWindowConfig.GetScreenNear(),
		rWindowConfig.GetScreenFar());

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

void CBaseCamera::UpdatePositionOffset(const float fDeltaTimeSec, DirectX::SimpleMath::Vector3& rOutOffset)
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

		switch (static_cast<eDir>(i))
		{
		case eDir::UP:
			rOutOffset += movementSpeed * m_DefaultUp * fDeltaTimeSec;
			break;
		case eDir::DOWN:
			rOutOffset -= movementSpeed * m_DefaultUp * fDeltaTimeSec;
			break;
		case eDir::LEFT:
			rOutOffset -= movementSpeed * m_DefaultRight * fDeltaTimeSec;
			break;
		case eDir::RIGHT:
			rOutOffset += movementSpeed * m_DefaultRight * fDeltaTimeSec;
			break;
		case eDir::FORWARD:
			rOutOffset += movementSpeed * m_DefaultForward * fDeltaTimeSec;
			break;
		case eDir::BACKWARDS:
			rOutOffset -= movementSpeed * m_DefaultForward * fDeltaTimeSec;
			break;
		}
	}
}
