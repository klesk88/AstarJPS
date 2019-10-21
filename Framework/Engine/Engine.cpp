#include "Engine.h"

#include "Camera/CameraTypes/BaseCamera.h"
#include "../Utils/DebugMacros.h"

CEngine::CEngine()
	: CSingleton<CEngine>(*this)
{}

CEngine::~CEngine()
{}

bool CEngine::Init()
{
	m_config.Load();
	m_window.Init(m_config);
	if (!m_renderer.Initialize(m_config, m_window.GetHWND()))
	{
		return false;
	}

	m_cameraManager.Init(m_config, m_inputManager);
	m_gameManager.Init(m_config, m_inputManager);
	m_picker.Init(m_inputManager);
	return true;
}

void CEngine::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the window or the user.
	while (true)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		const bool bFinish = msg.message == WM_QUIT
			|| m_inputManager.IsEscapePressed();

		if (bFinish)
		{
			break;
		}
		
		Update();
	}

	Shutdown();
}

void CEngine::Shutdown()
{
	m_cameraManager.Shutdown(m_inputManager);
	m_gameManager.Shutdown(m_inputManager);
	m_renderer.Shutdown();
}

void CEngine::Update()
{
	m_renderer.PreUpdate();

	m_cameraManager.Update();
	m_picker.Update();
	m_gameManager.Update();

	const CBaseCamera& rCurrentCamera = m_cameraManager.GetCurrentCamera();
	m_renderer.Update(rCurrentCamera.GetViewMatrix(), rCurrentCamera.GetProjMatrix());

	m_renderer.PostUpdate(m_config.GetVSyncEnable());
}
