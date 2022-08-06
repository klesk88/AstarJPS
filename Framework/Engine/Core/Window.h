#pragma once

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

//windows
#include <windows.h>

class CWindowConfig;

//class which represent the window we render
//on screen
class CWindow
{
public:
	CWindow();
	~CWindow() = default;

	void Init(const CWindowConfig& rConfig);
	[[nodiscard]] HWND GetHWND();
	[[nodiscard]] HINSTANCE GetInstance();

private:
	LPCSTR m_applicationName;
	HINSTANCE m_hInstance = nullptr;
	HWND m_hwnd = nullptr;
};

inline HWND CWindow::GetHWND() { return m_hwnd; }
inline HINSTANCE CWindow::GetInstance() { return m_hInstance; }