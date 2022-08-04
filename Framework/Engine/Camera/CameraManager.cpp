#include "Framework/Engine/Camera/CameraManager.h"

#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"
#include "Framework/Engine/Camera/CameraTypes/PerspectiveCamera.h"
#include "Framework/Engine/Camera/CameraTypes/TopDownCamera.h"
#include "Framework/Engine/Core/Config.h"
#include "Framework/Engine/Input/InputManager.h"

using namespace DirectX::SimpleMath;

CCameraManager::~CCameraManager()
{
	m_cameras.clear();
}

void CCameraManager::Init(const CConfig& rConfig, CInputManager& rInputManager)
{
	m_cameras.push_back(std::make_unique<CPerspectiveCamera>(rConfig, rInputManager));
	m_cameras.push_back(std::make_unique<CTopDownCamera>(rConfig, rInputManager));

	m_cameras[static_cast<int>(m_activeCameraType)]->SetActive();

    auto keyboardEventCbk = [this](const CKeyboardEvent& rKeyboardEvent) -> void {
        OnKeyboardEvent(rKeyboardEvent); 
	};

	m_keyboardEventId = rInputManager.KeyboardEvent.Attach(keyboardEventCbk);
}

void CCameraManager::Shutdown(CInputManager& rInputManager)
{
	for (int i = 0; i < m_cameras.size(); ++i)
	{
		m_cameras[i]->Shutdown(rInputManager);
	}

	m_cameras.clear();
	rInputManager.KeyboardEvent.Detach(m_keyboardEventId);
}

void CCameraManager::Update(const float fDeltaTimeSec)
{
	m_cameras[static_cast<int>(m_activeCameraType)]->Update(fDeltaTimeSec);
}

void CCameraManager::OnKeyboardEvent(const CKeyboardEvent& rKeyboardEvent)
{
	switch (rKeyboardEvent.GetType())
	{
	case CKeyboardEvent::EventType::KEYDOWN:
		OnKeyDown(rKeyboardEvent);
		break;
	default:
		break;
	}
}

void CCameraManager::OnKeyDown(const CKeyboardEvent& rKeyboardEvent)
{
	if (rKeyboardEvent.WasAlreadyPressed())
	{
		return;
	}

	eCameraTye newCameraType = eCameraTye::COUNT;
	switch (rKeyboardEvent.GetKeyCode())
	{
    case CKeyboardEvent::KeyCodes::KEY_1:
		newCameraType = eCameraTye::PERSPECTIVE;
        break;
    case CKeyboardEvent::KeyCodes::KEY_2:
		newCameraType = eCameraTye::TOP_DOWN;
        break;
	default:
		return;
	}

	if (newCameraType == eCameraTye::COUNT)
	{
		return;
	}

	m_cameras[static_cast<int>(m_activeCameraType)]->ClearActive();
	m_activeCameraType = newCameraType;
	m_cameras[static_cast<int>(m_activeCameraType)]->SetActive();
}
