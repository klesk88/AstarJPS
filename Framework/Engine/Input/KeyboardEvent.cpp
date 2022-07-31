#include "KeyboardEvent.h"

#include "../../Utils/DebugMacros.h"

CKeyboardEvent::CKeyboardEvent(const EventType eventType, const int iKeyCode, const bool bRepeated)
	: m_type(eventType)
	, m_keyCode(static_cast<KeyCodes>(iKeyCode))
	, m_bRepeated(bRepeated)
{
	ASSERT((iKeyCode >= static_cast<int>(KeyCodes::KEY_0) && iKeyCode <= static_cast<int>(KeyCodes::KEY_9)) || (iKeyCode >= static_cast<int>(KeyCodes::KEY_A) && iKeyCode <= static_cast<int>(KeyCodes::KEY_Z)));
}

