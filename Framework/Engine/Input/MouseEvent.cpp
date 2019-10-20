#include "MouseEvent.h"

CMouseEvent::CMouseEvent(const EventType eventType, const float fXPos, const float fYPos, const HWND hwnd)
	: m_Type(eventType)
	, m_fPosX(fXPos)
	, m_fPosY(fYPos)
	, m_Hwnd(hwnd)
	, m_fWheelDelta(0.f)
{}