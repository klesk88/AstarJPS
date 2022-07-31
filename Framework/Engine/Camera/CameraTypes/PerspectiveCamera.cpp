#include "Framework/Engine/Camera/CameraTypes/PerspectiveCamera.h"

#include "Framework/Engine/Core/Config.h"
#include "Framework/Engine/Engine.h"
#include "Framework/Engine/Input/InputManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CPerspectiveCamera::CPerspectiveCamera(const CConfig& rConfig, CInputManager& rInputManager)
	: CBaseCamera(rConfig, Vector3(0.3f, 0.5f, -0.7f), Vector3(0.0f, 1.0f, 0.0f), Vector3(0.f, 0.f, 1.f), Vector3(1.0, 0.f, 0.f), rInputManager)
{
	m_iWindowHeight = rConfig.GetScreenHeight();
	m_iWindowWidth = rConfig.GetScreenWidth();
}

CPerspectiveCamera::~CPerspectiveCamera()
{}

void CPerspectiveCamera::Update()
{
	Vector3 offset;
	UpdatePositionOffset(offset);

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

void CPerspectiveCamera::OnMouseEvent(const CMouseEvent& rMouseEvent)
{
	if (!IsActive())
	{
		return;
	}

	switch (rMouseEvent.GetEventType())
	{
	case CMouseEvent::MOUSE_ENTER_FOCUS:
		break;
	case CMouseEvent::MOUSE_LOST_FOCUS: 
		OnRightMouseButtonRelease();
		break;
	case CMouseEvent::MOUSE_MOVE:
		OnMouseMove(rMouseEvent);
		break;
	case CMouseEvent::MOUSE_RIGHT_BTN_DOWN:
		OnRightMouseButtonPress(rMouseEvent.GetHwnd());
		break;
	case CMouseEvent::MOUSE_RIGHT_BTN_UP:
		OnRightMouseButtonRelease();
		break;
	default:
		break;
	}
}

void CPerspectiveCamera::OnRightMouseButtonPress(HWND hwnd)
{
	//when we press the right button to rotate the camera,
	//force the mouse to be always inside the window and hide it

	RECT rcClient;
	POINT ptClientUL; 
	POINT ptClientLR;
	SetCapture(hwnd);
	GetClientRect(hwnd, &rcClient);

	ptClientUL.x = 0;
	ptClientUL.y = 0;

	ptClientLR.x = m_iWindowWidth;
	ptClientLR.y = m_iWindowHeight;
	ClientToScreen(hwnd, &ptClientUL);
	ClientToScreen(hwnd, &ptClientLR);

	SetRect(&rcClient, ptClientUL.x, ptClientUL.y,
		ptClientLR.x, ptClientLR.y);
	ClipCursor(&rcClient);

	m_bRightMouseBtnpress = true;
	ShowCursor(false);
}

void CPerspectiveCamera::OnRightMouseButtonRelease()
{
	if (!m_bRightMouseBtnpress)
	{
		return;
	}

	m_bRightMouseBtnpress = false;
	ClipCursor(nullptr);
	ReleaseCapture();
	ShowCursor(true);
}

void CPerspectiveCamera::OnMouseMove(const CMouseEvent& rMouseEvent)
{
	//when we are in rotation camera mode, get the offset from the center
	//of the window and reset the mouse to the central position.

	if (!m_bRightMouseBtnpress)
	{
		return;
	}

	POINT ptClient;   
	ptClient.x = static_cast<long>(m_iWindowWidth * 0.5f);
	ptClient.y = static_cast<long>(m_iWindowHeight * 0.5f);

	const int iDiffX = static_cast<int>(rMouseEvent.GetPosX() - ptClient.x);
	const int iDiffY = static_cast<int>(rMouseEvent.GetPosY() - ptClient.y);

	if (iDiffX == 0 && iDiffY == 0)
	{
		return;
	}

	m_fYaw += XMConvertToRadians(iDiffX * m_fRotationSpeed);
	m_fPitch += XMConvertToRadians(iDiffY * m_fRotationSpeed);

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

	ClientToScreen(rMouseEvent.GetHwnd(), &ptClient);
	SetCursorPos(ptClient.x, ptClient.y);
}
