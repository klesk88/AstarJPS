#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"

//framework
#include "Framework/Engine/Camera/Config/CameraConfigBase.h"
#include "Framework/Engine/Core/WindowConfig.h"
#include "Framework/Engine/Engine.h"
#include "Framework/Engine/ManagerUpdateInput.h"
#include "Framework/Engine/Input/KeyboardMouse/Keyboard/InputKeyboardState.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

CBaseCamera::CBaseCamera(const CWindowConfig& rWindowConfig, const CCameraConfigBase& rCameraConfig, const eCameraTye cameraType, const Vector3& rPosition, const Vector3& rDefaultUp, const Vector3& rDefaultFwd, const Vector3& rDefaultRight)
	: m_DefaultUp(rDefaultUp)
	, m_DefaultForward(rDefaultFwd)
	, m_DefaultRight(rDefaultRight)
	, m_vPosition(rPosition)
	, m_fMovementSpeed(rCameraConfig.GetMovementSpeed())
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
}

void CBaseCamera::Shutdown()
{
}

void CBaseCamera::UpdatePositionOffset(const CManagerUpdateInput& rInput, DirectX::SimpleMath::Vector3& rOutOffset)
{
	const Vector3 movementSpeed(m_fMovementSpeed, m_fMovementSpeed, m_fMovementSpeed);
	rOutOffset = Vector3(0.f, 0.f, 0.f);
	const CInputKeyboardState& rKeyboardState = rInput.GetKeyboardState();

    if (rKeyboardState.IsPressed(KeyboardKeyCodes::KeyCodes::KEY_Q))
    {
        rOutOffset += movementSpeed * m_DefaultUp * rInput.GetDeltaTime();
    }
    else if (rKeyboardState.IsPressed(KeyboardKeyCodes::KeyCodes::KEY_E))
    {
        rOutOffset -= movementSpeed * m_DefaultUp * rInput.GetDeltaTime();
    }
    else if (rKeyboardState.IsPressed(KeyboardKeyCodes::KeyCodes::KEY_A))
    {
        rOutOffset -= movementSpeed * m_DefaultRight * rInput.GetDeltaTime();
    }
    else if (rKeyboardState.IsPressed(KeyboardKeyCodes::KeyCodes::KEY_D))
    {
        rOutOffset += movementSpeed * m_DefaultRight * rInput.GetDeltaTime();
    }
    if (rKeyboardState.IsPressed(KeyboardKeyCodes::KeyCodes::KEY_W))
    {
        rOutOffset += movementSpeed * m_DefaultForward * rInput.GetDeltaTime();
    }
    else if (rKeyboardState.IsPressed(KeyboardKeyCodes::KeyCodes::KEY_S))
    {
        rOutOffset -= movementSpeed * m_DefaultForward * rInput.GetDeltaTime();
    }
}
