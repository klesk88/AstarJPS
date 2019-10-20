#pragma once

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

#include "MouseEvent.h"
#include "KeyboardEvent.h"
#include "../../Utils/ClassMacros.h"
#include "../Core/Event.h"

class CConfig;

class CInputManager
{
	NON_COPYABLE_CLASS(CInputManager)

public:
	CEventHandler<CMouseEvent> MouseEvent;
	CEventHandler<CKeyboardEvent> KeyboardEvent;

public:
	CInputManager();
	~CInputManager();
	
	bool HandleWindowsMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
	inline bool IsEscapePressed() const { return m_bEscapePress; }
private:
	bool HandleMouseMessages(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
	bool HandleKeyboardMessages(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);

private:
	int m_iMouseX;
	int m_iMouseY;
	bool m_bTrackingMouse : 1;
	bool m_bEscapePress : 1;
};