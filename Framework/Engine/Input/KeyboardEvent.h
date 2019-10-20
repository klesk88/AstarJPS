#pragma once

class CKeyboardEvent
{
public:
	enum class EventType
	{
		KEYUP = 0,
		KEYDOWN,

		COUNT
	};

	enum class KeyCodes
	{
		KEY_0 = 0x30,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_A = 0x41,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z
	};

public:
	CKeyboardEvent(const EventType eventType, const int iKeyCode, const bool bRepeated);

	bool IsValid() const { return m_type != EventType::COUNT; }
	static bool IsKeyCodeSupported(const int iKeyCode);
	KeyCodes GetKeyCode() const { return m_keyCode; }
	EventType GetType() const { return m_type; }
	bool WasAlreadyPressed() const { return m_bRepeated; }

private:
	const EventType m_type;
	const KeyCodes m_keyCode;
	const bool m_bRepeated;
};