#pragma once

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

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
	explicit CKeyboardEvent(const EventType eventType, const int iKeyCode, const bool bRepeated);
	~CKeyboardEvent() = default;

	[[nodiscard]] constexpr bool IsValid() const;
	[[nodiscard]] static constexpr bool IsKeyCodeSupported(const int iKeyCode);
	[[nodiscard]] constexpr KeyCodes GetKeyCode() const;
	[[nodiscard]] constexpr EventType GetType() const;
	[[nodiscard]] constexpr bool WasAlreadyPressed() const;

private:
	const EventType m_type = EventType::COUNT;
	const KeyCodes m_keyCode = KeyCodes::KEY_0;
	const bool m_bRepeated = false;
};

inline constexpr bool CKeyboardEvent::IsValid() const { return m_type != EventType::COUNT; }
inline constexpr CKeyboardEvent::KeyCodes CKeyboardEvent::GetKeyCode() const { return m_keyCode; }
inline constexpr CKeyboardEvent::EventType CKeyboardEvent::GetType() const { return m_type; }
inline constexpr bool CKeyboardEvent::WasAlreadyPressed() const { return m_bRepeated; }
inline constexpr bool CKeyboardEvent::IsKeyCodeSupported(const int iKeyCode)
{
    return (iKeyCode >= static_cast<int>(KeyCodes::KEY_0) && iKeyCode <= static_cast<int>(KeyCodes::KEY_9)) || (iKeyCode >= static_cast<int>(KeyCodes::KEY_A) && iKeyCode <= static_cast<int>(KeyCodes::KEY_Z));
}
