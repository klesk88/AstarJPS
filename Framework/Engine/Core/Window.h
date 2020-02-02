#pragma once

//class which represent the window we render
//on screen

#include <windows.h>

class CConfig;

class CWindow
{
public:
	CWindow();
	~CWindow();

	void Init(CConfig& rConfig);
	HWND GetHWND() { return m_hwnd; }
	HINSTANCE GetInstance() { return m_hInstance; }

private:
	LPCSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hwnd;
};