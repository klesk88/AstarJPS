#pragma once

#include "Camera/CameraManager.h"
#include "Core/Config.h"
#include "Core/Window.h"
#include "GameManager.h"
#include "Render/Renderer.h"
#include "Input/InputManager.h"
#include "../Utils/Picker/Picker.h"
#include "../Utils/Singleton.h"

class CEngine final : public CSingleton<CEngine>
{
public:
	CEngine();
	~CEngine();

	bool Init();
	void Run();
	void Update();

	const CCameraManager& GetCameraManager() const { return m_cameraManager; }
	const CConfig& GetConfig() const { return m_config; }
	const CWindow& GetSystem() const { return m_window; }
	CRenderer& GetRenderer() { return m_renderer; }
	CInputManager& GetInputManager() { return m_inputManager; }
	CGameManager& GetGameManager() { return m_gameManager; }
	CPicker& GetPicker() { return m_picker; }

	HWND GetHWND() { return m_window.GetHWND(); }

private:
	void Shutdown();

private:
	CConfig m_config;
	CGameManager m_gameManager;
	CInputManager m_inputManager;
	CCameraManager m_cameraManager;
	CRenderer m_renderer;
	CWindow m_window;

	CPicker m_picker;
};