#pragma once

#include "Framework/Engine/Camera/CameraManager.h"
#include "Framework/Engine/Core/Config.h"
#include "Framework/Engine/Core/Window.h"
#include "Framework/Engine/GameManager.h"
#include "Framework/Engine/Render/Renderer.h"
#include "Framework/Engine/Input/InputManager.h"
#include "Framework/Utils/Picker/Picker.h"
#include "Framework/Utils/Singleton.h"
#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

class CEngine final : public CSingleton<CEngine>
{
public:
	CEngine();
	~CEngine() = default;

	[[nodiscard]] bool Init();

	void Run();
	void Update();

	[[nodiscard]] const CCameraManager& GetCameraManager() const;
	[[nodiscard]] const CConfig& GetConfig() const;
	[[nodiscard]] const CWindow& GetSystem() const;
	[[nodiscard]] CRenderer& GetRenderer();
	[[nodiscard]] CInputManager& GetInputManager();
	[[nodiscard]] CGameManager& GetGameManager();
	[[nodiscard]] CPicker& GetPicker();
	[[nodiscard]] HWND GetHWND();

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

inline const CCameraManager& CEngine::GetCameraManager() const { return m_cameraManager; }
inline const CConfig& CEngine::GetConfig() const { return m_config; }
inline const CWindow& CEngine::GetSystem() const { return m_window; }
inline CRenderer& CEngine::GetRenderer() { return m_renderer; }
inline CInputManager& CEngine::GetInputManager() { return m_inputManager; }
inline CGameManager& CEngine::GetGameManager() { return m_gameManager; }
inline CPicker& CEngine::GetPicker() { return m_picker; }
inline HWND CEngine::GetHWND() { return m_window.GetHWND(); }