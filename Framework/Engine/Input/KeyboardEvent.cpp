#include "KeyboardEvent.h"

#include "../../Utils/DebugMacros.h"

CKeyboardEvent::CKeyboardEvent(const EventType eventType, const int iKeyCode, const bool bRepeated)
	: m_type(eventType)
	, m_keyCode((KeyCodes)iKeyCode)
	, m_bRepeated(bRepeated)
{
	ASSERT((iKeyCode >= (int)KeyCodes::KEY_0 && iKeyCode <= (int)KeyCodes::KEY_9) || (iKeyCode >= (int)KeyCodes::KEY_A && iKeyCode <= (int)KeyCodes::KEY_Z));
}

bool CKeyboardEvent::IsKeyCodeSupported(const int iKeyCode)
{
	return (iKeyCode >= (int)KeyCodes::KEY_0 && iKeyCode <= (int)KeyCodes::KEY_9) || (iKeyCode >= (int)KeyCodes::KEY_A && iKeyCode <= (int)KeyCodes::KEY_Z);
}

