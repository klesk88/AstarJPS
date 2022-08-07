#include "Framework/Engine/Camera/CameraManager.h"

#include "Framework/Engine/Camera/CameraTypes/BaseCamera.h"
#include "Framework/Engine/Camera/CameraTypes/PerspectiveCamera.h"
#include "Framework/Engine/Camera/CameraTypes/TopDownCamera.h"
#include "Framework/Engine/Camera/Config/CameraConfigBase.h"
#include "Framework/Engine/Core/Config.h"
#include "Framework/Engine/Input/KeyboardMouse/Keyboard/InputKeyboardState.h"
#include "Framework/Engine/ManagerUpdateInput.h"

using namespace DirectX::SimpleMath;

CCameraManager::~CCameraManager()
{
	m_cameras.clear();
}

void CCameraManager::Init(const CConfig& rConfig)
{
	const CCameraManagerConfig& rManagerConfig = rConfig.GetCameraManagerConfig();
	for (const std::unique_ptr<CCameraConfigBase>& rCameraConfig : rConfig.GetCameraConfigs())
	{
		m_cameras.push_back(rCameraConfig->GetCameraInstance(rConfig.GetWindowConfig()));
		CBaseCamera* pNewCamera = m_cameras[m_cameras.size() - 1].get();
		if (pNewCamera->GetCameraType() == rManagerConfig.GetStartCameraType())
		{
			pNewCamera->SetActive();
			m_pCurrentCamera = pNewCamera;
		}
	}
}

void CCameraManager::Shutdown()
{
	for (int i = 0; i < m_cameras.size(); ++i)
	{
		m_cameras[i]->Shutdown();
	}

	m_cameras.clear();
	m_pCurrentCamera = nullptr;
}

void CCameraManager::Update(const CManagerUpdateInput& rInput)
{
	UpdateKeyboardInput(rInput);
	m_pCurrentCamera->Update(rInput);
}

void CCameraManager::UpdateKeyboardInput(const CManagerUpdateInput& rInput)
{
	const CInputKeyboardState& rKeyboardState = rInput.GetKeyboardState();
	eCameraTye newCameraType = eCameraTye::COUNT;

	if (rKeyboardState.WasPressed(KeyboardKeyCodes::KeyCodes::KEY_1))
	{
		newCameraType = eCameraTye::PERSPECTIVE;
	}
	else if (rKeyboardState.WasPressed(KeyboardKeyCodes::KeyCodes::KEY_2))
	{
		newCameraType = eCameraTye::TOP_DOWN;
	}

    if (newCameraType == eCameraTye::COUNT)
    {
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
}
