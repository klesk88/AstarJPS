#pragma once

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

//windows
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
	explicit CMouseEvent(const EventType eventType, const float fXPos, const float fYPos, const HWND hwnd);
	~CMouseEvent() = default;

	[[nodiscard]] EventType GetEventType() const;
	[[nodiscard]] HWND GetHwnd() const;
	[[nodiscard]] float GetPosX() const;
	[[nodiscard]] float GetPosY() const;

	void SetWheelDelta(const float fDelta);
	[[nodiscard]] float GetWheelDelta() const;

private:
	const float m_fPosX = 0.f;
	const float m_fPosY = 0.f;
	float m_fWheelDelta = 0.f;
	const HWND m_Hwnd;
	const EventType m_Type = EventType::COUNT;
};

inline CMouseEvent::EventType CMouseEvent::GetEventType() const { return m_Type; }
inline HWND CMouseEvent::GetHwnd() const { return m_Hwnd; }
inline float CMouseEvent::GetPosX() const { return m_fPosX; }
inline float CMouseEvent::GetPosY() const { return m_fPosY; }
inline void CMouseEvent::SetWheelDelta(const float fDelta) { m_fWheelDelta = fDelta; }
inline float CMouseEvent::GetWheelDelta() const { return m_fWheelDelta; }