#pragma once

#include <windows.h>

class CMouseEvent
{
public:
	enum EventType
	{
		MOUSE_MOVE = 0,
		MOUSE_LEFT_BTN_UP,
		MOUSE_LEFT_BTN_DOWN,
		MOUSE_RIGHT_BTN_UP,
		MOUSE_RIGHT_BTN_DOWN,
		MOUSE_LOST_FOCUS,
		MOUSE_ENTER_FOCUS,
		MOUSE_WHEEL,

		COUNT
	};

public:
	CMouseEvent(const EventType eventType, const float fXPos, const float fYPos, const HWND hwnd);

	EventType GetEventType() const { return m_Type; }
	HWND GetHwnd() const { return m_Hwnd; }
	float GetPosX() const { return m_fPosX; }
	float GetPosY() const { return m_fPosY; }

	void SetWheelDelta(const float fDelta) { m_fWheelDelta = fDelta; }
	float GetWheelDelta() const { return m_fWheelDelta; }

private:
	const EventType m_Type;
	const float m_fPosX;
	const float m_fPosY;
	const HWND m_Hwnd;

	float m_fWheelDelta;
};