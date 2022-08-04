#pragma once

#include "Framework/Engine/Camera/CameraManager.h"
#include "Framework/Engine/Core/Config.h"
#include "Framework/Engine/Core/Window.h"
#include "Framework/Engine/GameManager.h"
#include "Framework/Engine/Input/InputManager.h"
#include "Framework/Engine/Render/Renderer.h"
#include "Framework/Utils/Imgui/imgui.h"
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

	[[nodiscard]] const CCameraManager& GetCameraManager() const;
	[[nodiscard]] const CConfig& GetConfig() const;
	[[nodiscard]] const CWindow& GetSystem() const;
	[[nodiscard]] CRenderer& GetRenderer();
	[[nodiscard]] CInputManager& GetInputManager();
	[[nodiscard]] CGameManager& GetGameManager();
	[[nodiscard]] CPicker& GetPicker();
	[[nodiscard]] HWND GetHWND();

private:
	[[nodiscard]] float Update();
	void Shutdown();
	void AddTickCount();
	void StoreTickCount();
	[[nodiscard]] bool IterateWindowsMessagesGetIfQuit() const;
	void OnPostUpdate(const float fPrevDeltaTime);

	void OnImguiUpdate();

private:
	CConfig m_config;
	CGameManager m_gameManager;
	CInputManager m_inputManager;
	CCameraManager m_cameraManager;
	CRenderer m_renderer;
	CWindow m_window;
	CPicker m_picker;
	CEventId m_imguiEventId = CEventId::GetInvalidID();
	std::vector<int> m_tickSamples;
	float m_fLastTickSampleStartTime = 0.f;
	float m_flastDeltaTimeSec = 0.f;
    int m_iTickIndex = 0;
	int m_iCurrentTickCount = 0;
    int m_iTickSum = 0;
	bool m_bHasFilledTickSampleArray = false;
};

inline const CCameraManager& CEngine::GetCameraManager() const { return m_cameraManager; }
inline const CConfig& CEngine::GetConfig() const { return m_config; }
inline const CWindow& CEngine::GetSystem() const { return m_window; }
inline CRenderer& CEngine::GetRenderer() { return m_renderer; }
inline CInputManager& CEngine::GetInputManager() { return m_inputManager; }
inline CGameManager& CEngine::GetGameManager() { return m_gameManager; }
inline CPicker& CEngine::GetPicker() { return m_picker; }
inline HWND CEngine::GetHWND() { return m_window.GetHWND(); }
inline void CEngine::AddTickCount() { ++m_iCurrentTickCount; }