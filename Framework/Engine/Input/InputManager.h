#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include "Framework/Engine/Core/Event.h"
#include "Framework/Engine/Input/KeyboardEvent.h"
#include "Framework/Engine/Input/MouseEvent.h"
#include "Framework/Utils/ClassMacros.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//input
#include <dinput.h>

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

class CConfig;

class CInputManager
{
	NON_COPYABLE_CLASS(CInputManager)

public:
	CEventHandler<CMouseEvent> MouseEvent;
	CEventHandler<CKeyboardEvent> KeyboardEvent;

public:
	CInputManager() = default;
	~CInputManager() = default;
	
	[[nodiscard]] bool HandleWindowsMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
	[[nodiscard]] bool IsEscapePressed() const;

private:
	[[nodiscard]] bool HandleMouseMessages(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
	[[nodiscard]] bool HandleKeyboardMessages(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

private:
	int m_iMouseX = INT32_MAX;
	int m_iMouseY = INT32_MAX;
	bool m_bTrackingMouse = false;
	bool m_bEscapePress = false;
};

inline bool CInputManager::IsEscapePressed() const { return m_bEscapePress; }