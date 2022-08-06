#include "Framework/Engine/Camera/CameraManager.h"

#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"
#include "Framework/Engine/Camera/CameraTypes/PerspectiveCamera.h"
#include "Framework/Engine/Camera/CameraTypes/TopDownCamera.h"
#include "Framework/Engine/Camera/Config/CameraConfigBase.h"
#include "Framework/Engine/Core/Config.h"
#include "Framework/Engine/Input/InputManager.h"

using namespace DirectX::SimpleMath;

CCameraManager::~CCameraManager()
{
	m_cameras.clear();
}

void CCameraManager::Init(const CConfig& rConfig, CInputManager& rInputManager)
{
	const CCameraManagerConfig& rManagerConfig = rConfig.GetCameraManagerConfig();
	for (const std::unique_ptr<CCameraConfigBase>& rCameraConfig : rConfig.GetCameraConfigs())
	{
		m_cameras.push_back(rCameraConfig->GetCameraInstance(rConfig.GetWindowConfig(), rInputManager));
		CBaseCamera* pNewCamera = m_cameras[m_cameras.size() - 1].get();
		if (pNewCamera->GetCameraType() == rManagerConfig.GetStartCameraType())
		{
			pNewCamera->SetActive();
			m_pCurrentCamera = pNewCamera;
		}
	}

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
	m_pCurrentCamera = nullptr;
}

void CCameraManager::Update(const float fDeltaTimeSec)
{
	m_pCurrentCamera->Update(fDeltaTimeSec);
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
		ASSERT(false);
		return;
	}

	m_pCurrentCamera->ClearActive();
	m_pCurrentCamera = nullptr;

    for (std::unique_ptr<CBaseCamera>& rCamera : m_cameras)
    {
        if (rCamera->GetCameraType() == newCameraType)
        {
            rCamera->SetActive();
			m_pCurrentCamera = rCamera.get();
			break;
        }
    }

	ASSERT(m_pCurrentCamera != nullptr);
}
