#include "Framework/Engine/Input/InputManager.h"

#include "Framework/Engine/Core/Config.h"
#include "Framework/Utils/DebugMacros.h"
#include "Framework/Utils/Imgui/imgui.h"

bool CInputManager::HandleWindowsMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	if (HandleKeyboardMessages(hwnd, umessage, wparam, lparam))
	{
		return true;
	}

	if (HandleMouseMessages(hwnd, umessage, wparam, lparam))
	{
		return true;
	}

	return false;
}

bool CInputManager::HandleMouseMessages(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	//user is using the imgui avoid to capture input on it
	if (ImGui::GetCurrentContext() && ImGui::GetIO().WantCaptureMouse)
	{
		return false;
	}

	int iX = INT32_MAX;
	int iY = INT32_MAX;
	float fWheelDelta = 0.f;
	CMouseEvent::EventType eventSelected = CMouseEvent::COUNT;

	switch (umessage)
	{
	case WM_MOUSEMOVE:
	{
		iX = LOWORD(lparam);
		iY = HIWORD(lparam);

		if (!m_bTrackingMouse)
		{
			TRACKMOUSEEVENT trackMouseevent;
			ZeroMemory(&trackMouseevent, sizeof(TRACKMOUSEEVENT));
			trackMouseevent.cbSize = sizeof(TRACKMOUSEEVENT);
			trackMouseevent.dwFlags = TME_LEAVE;
			trackMouseevent.hwndTrack = hwnd;

			m_bTrackingMouse = true;
			TrackMouseEvent(&trackMouseevent);

			eventSelected = CMouseEvent::MOUSE_ENTER_FOCUS;
		}
		else if (iX != m_iMouseX && iY != m_iMouseY)
		{
			eventSelected = CMouseEvent::MOUSE_MOVE;
		}
		else
		{
			return true;
		}

		m_iMouseX = iX;
		m_iMouseY = iY;
		break;
	}
	case WM_MOUSELEAVE:
	{
		m_bTrackingMouse = false;
		iX = UINT32_MAX;
		iY = UINT32_MAX;
		eventSelected = CMouseEvent::MOUSE_LOST_FOCUS;
		break;
	}
	case WM_RBUTTONDOWN:
	{
		iX = LOWORD(lparam);
		iY = HIWORD(lparam);
		eventSelected = CMouseEvent::MOUSE_RIGHT_BTN_DOWN;
		break;
	}
	case WM_RBUTTONUP:
	{
		iX = LOWORD(lparam);
		iY = HIWORD(lparam);
		eventSelected = CMouseEvent::MOUSE_RIGHT_BTN_UP;
		break;
	}
	case WM_LBUTTONDOWN:
	{
		iX = LOWORD(lparam);
		iY = HIWORD(lparam);
		eventSelected = CMouseEvent::MOUSE_LEFT_BTN_DOWN;
		break;
	}
	case WM_LBUTTONUP:
	{
		iX = LOWORD(lparam);
		iY = HIWORD(lparam);
		eventSelected = CMouseEvent::MOUSE_LEFT_BTN_UP;
		break;
	}
	case WM_MOUSEWHEEL:
	{
		fWheelDelta = GET_WHEEL_DELTA_WPARAM(wparam);
		eventSelected = CMouseEvent::MOUSE_WHEEL;
		break;
	}
	default:
		return false;
	}

	ASSERT(eventSelected != CMouseEvent::COUNT);
	CMouseEvent mouseEvent(eventSelected, static_cast<float>(iX), static_cast<float>(iY), hwnd);
	mouseEvent.SetWheelDelta(fWheelDelta);
	MouseEvent.Emit(mouseEvent);
	return true;
}

bool CInputManager::HandleKeyboardMessages(HWND /*hwnd*/, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
	case WM_KEYUP:
		//just listen to key events which we actually support currently
		if (!CKeyboardEvent::IsKeyCodeSupported(static_cast<int>(wparam)))
		{
			return false;
		}

		KeyboardEvent.Emit(CKeyboardEvent{ CKeyboardEvent::EventType::KEYUP, static_cast<int>(wparam), false });
		break;
	case WM_KEYDOWN:
	{
		//user is using the imgui avoid to capture input on it
		if (ImGui::GetCurrentContext() && ImGui::GetIO().WantCaptureKeyboard)
		{
			return false;
		}

		const bool bWasAlreadyPressed = lparam & 0x40000000;
		if (!bWasAlreadyPressed && wparam == VK_ESCAPE)
		{
			m_bEscapePress = true;
		}

		//just listen to key events which we actually support currently
		if (!CKeyboardEvent::IsKeyCodeSupported(static_cast<int>(wparam)))
		{
			return false;
		}

		KeyboardEvent.Emit(CKeyboardEvent{ CKeyboardEvent::EventType::KEYDOWN, static_cast<int>(wparam), bWasAlreadyPressed });
		break;
	}
	default:
		return false;
	}

	return true;
}
