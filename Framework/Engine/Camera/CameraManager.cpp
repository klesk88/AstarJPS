#include "CameraManager.h"

#include "CameraTypes/BaseCamera.h"
#include "CameraTypes/TopDownCamera.h"
#include "CameraTypes/PerspectiveCamera.h"
#include "../Core/Config.h"
#include "../Input/InputManager.h"

using namespace DirectX::SimpleMath;

CCameraManager::CCameraManager()
	: m_activeCameraType(eCameraTye::TOP_DOWN)
{}

CCameraManager::~CCameraManager()
{
	for (int i = 0; i < m_cameras.size(); ++i)
	{
		delete m_cameras[i];
	}

	m_cameras.clear();
}

void CCameraManager::Init(const CConfig& rConfig, CInputManager& rInputManager)
{
	m_cameras.push_back(new CPerspectiveCamera(rConfig, rInputManager));
	m_cameras.push_back(new CTopDownCamera(rConfig, rInputManager));

	m_cameras[m_activeCameraType]->SetActive();

	m_keyboardEventId = rInputManager.KeyboardEvent.Attach([this](const CKeyboardEvent& rKeyboardEvent) { OnKeyboardEvent(rKeyboardEvent); });
}

void CCameraManager::Update()
{
	m_cameras[m_activeCameraType]->Update();
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

	if (rKeyboardEvent.GetKeyCode() == CKeyboardEvent::KeyCodes::KEY_1)
	{
		newCameraType = eCameraTye::PERSPECTIVE;
	}
	else if (rKeyboardEvent.GetKeyCode() == CKeyboardEvent::KeyCodes::KEY_2)
	{
		newCameraType = eCameraTye::TOP_DOWN;
	}

	if (newCameraType == eCameraTye::COUNT)
	{
		return;
	}

	m_cameras[m_activeCameraType]->ClearActive();
	m_activeCameraType = newCameraType;
	m_cameras[newCameraType]->SetActive();
}
