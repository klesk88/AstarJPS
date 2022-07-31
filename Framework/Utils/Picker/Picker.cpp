#include "Framework/Utils/Picker/Picker.h"

#include "Framework/Engine/Camera/CameraManager.h"
#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"
#include "Framework/Engine/Collision/CollisionHelpers.h"
#include "Framework/Engine/Core/Config.h"
#include "Framework/Engine/Engine.h"
#include "Framework/Engine/Input/InputManager.h"

using namespace DirectX::SimpleMath;

void CPicker::Init(CInputManager& rInputManager)
{
	m_mouseEventId = rInputManager.MouseEvent.Attach([this](const CMouseEvent& rMouseEvent) { OnMouseEvent(rMouseEvent); });
}

void CPicker::Shutdown(CInputManager& rInputManager)
{
	rInputManager.MouseEvent.Detach(m_mouseEventId);
}

void CPicker::Update()
{
	if (m_bNewEvent)
	{
		PickerEvent.Emit(CPickerEvent(m_vStartPos, m_vEndPos));
	}

	m_bNewEvent = false;
}

void CPicker::OnMouseEvent(const CMouseEvent& rMouseEvent)
{
	switch (rMouseEvent.GetEventType())
	{
	case CMouseEvent::MOUSE_LEFT_BTN_UP:
		HandleMouseBtnUp(rMouseEvent);
		break;
	default:
		break;
	}
}

void CPicker::HandleMouseBtnUp(const CMouseEvent& rMouseEvent)
{
	ComputeMouseStartEndPos(rMouseEvent, m_vStartPos, m_vEndPos);
	m_bNewEvent = true;
}

void CPicker::ComputeMouseStartEndPos(const CMouseEvent& rMouseEvent, Vector3& rOutStart, Vector3& rOutEnd) const
{
	CEngine* pEngine = CEngine::GetInstance();
	const CConfig& rConfig = pEngine->GetConfig();
	const CCameraManager& rCameraManager = pEngine->GetCameraManager();
	const CBaseCamera& rBaseCamera = rCameraManager.GetCurrentCamera();
	const Matrix viewTranInv = rBaseCamera.GetInvViewMatrix();
	const Matrix projTranInv = rBaseCamera.GetInvProjMatrix();
	const Vector3 nearPlane(rConfig.GetScreenNear(), rConfig.GetScreenNear(), rConfig.GetScreenNear());
	const Vector3 farPlane(rConfig.GetScreenFar(), rConfig.GetScreenFar(), rConfig.GetScreenFar());

	//bring coordinates in the -1 1 space
	const float fPointX = (rMouseEvent.GetPosX() / (rConfig.GetScreenWidth() * 0.5f)) - 1.f;
	const float fPointY = 1.f - (rMouseEvent.GetPosY() / (rConfig.GetScreenHeight() * 0.5f));

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
