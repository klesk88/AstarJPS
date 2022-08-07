#include "Framework/Utils/Picker/Picker.h"

#include "Framework/Engine/Camera/CameraManager.h"
#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"
#include "Framework/Engine/Collision/CollisionHelpers.h"
#include "Framework/Engine/Core/Config.h"
#include "Framework/Engine/Core/WindowConfig.h"
#include "Framework/Engine/Engine.h"
#include "Framework/Engine/Input/KeyboardMouse/Mouse/InputMouseState.h"
#include "Framework/Engine/ManagerUpdateInput.h"

using namespace DirectX::SimpleMath;

void CPicker::Init()
{
}

void CPicker::Shutdown()
{
}

void CPicker::Update(const CManagerUpdateInput& rInput)
{
    const CInputMouseState& rMouseState = rInput.GetMouseState();
	if (!rMouseState.WasPressed(MouseKeyCodes::KeyCodes::LEFT_BUTTON))
	{
		return;
	}

    DirectX::SimpleMath::Vector3 vStartPos;
    DirectX::SimpleMath::Vector3 vEndPos;
    ComputeMouseStartEndPos(rMouseState, vStartPos, vEndPos);
    PickerEvent.Emit(CPickerEvent(vStartPos, vEndPos));
}

void CPicker::ComputeMouseStartEndPos(const CInputMouseState& rMouseState, Vector3& rOutStart, Vector3& rOutEnd) const
{
	CEngine* pEngine = CEngine::GetInstance();
	const CConfig& rConfig = pEngine->GetConfig();
	const CWindowConfig& rWindowConfig = rConfig.GetWindowConfig();
	const CCameraManager& rCameraManager = pEngine->GetCameraManager();
	const CBaseCamera& rBaseCamera = rCameraManager.GetCurrentCamera();
	const Matrix viewTranInv = rBaseCamera.GetInvViewMatrix();
	const Matrix projTranInv = rBaseCamera.GetInvProjMatrix();
	const Vector3 nearPlane(rWindowConfig.GetScreenNear(), rWindowConfig.GetScreenNear(), rWindowConfig.GetScreenNear());
	const Vector3 farPlane(rWindowConfig.GetScreenFar(), rWindowConfig.GetScreenFar(), rWindowConfig.GetScreenFar());

	//bring coordinates in the -1 1 space
	const float fPointX = (rMouseState.GetMousePositionX() / (rWindowConfig.GetScreenWidth() * 0.5f)) - 1.f;
	const float fPointY = 1.f - (rMouseState.GetMousePositionY() / (rWindowConfig.GetScreenHeight() * 0.5f));

	Vector3 vMouseCameraNear(fPointX, fPointY, 1.f);
	Vector3 vMouseCameraFar(fPointX, fPointY, 1.f);

	//eye space
	vMouseCameraNear = Vector3::Transform(vMouseCameraNear, projTranInv);
	vMouseCameraFar = Vector3::Transform(vMouseCameraFar, projTranInv);

	vMouseCameraNear *= nearPlane;
	vMouseCameraFar *= farPlane;

	//world space
	vMouseCameraNear = Vector3::Transform(vMouseCameraNear, viewTranInv);
	vMouseCameraFar = Vector3::Transform(vMouseCameraFar, viewTranInv);

	rOutStart = vMouseCameraNear;
	rOutEnd = vMouseCameraFar;
}
