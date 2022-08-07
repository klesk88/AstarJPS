#pragma once

#include "Framework/Engine/Input/InputCommonIncludes.h"
#include "Framework/Utils/DebugMacros.h"

//std
#include <type_traits>

namespace KeyboardKeyCodes
{
	enum class KeyCodes
	{
		KEY_0 = 0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_A,
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
		KEY_Z,
		KEY_ESCAPE,

		KEY_COUNT
	};

    constexpr int StartNumberKeyCode = 0x30;
    constexpr int EndNumberKeyCode = 0x30 + static_cast<int>(KeyCodes::KEY_9);
    constexpr int StartLetterKeyCode = 0x41;
	constexpr int EndLetterKeyCode = 0x41 + (static_cast<int>(KeyCodes::KEY_Z) - static_cast<int>(KeyCodes::KEY_A));

    [[nodiscard]] inline constexpr bool IsKeyCodeNumber(const uintptr_t iKeyCode)
    {
        return iKeyCode >= StartNumberKeyCode && iKeyCode <= EndNumberKeyCode;
    }

    [[nodiscard]] inline constexpr bool IsKeyCodeLetter(const uintptr_t uKeyCode)
    {
        return uKeyCode >= StartLetterKeyCode && uKeyCode <= EndLetterKeyCode;
    }

    [[nodiscard]] inline constexpr bool IsKeyCodeSupported(const uintptr_t uKeyCode)
    {
		return IsKeyCodeNumber(uKeyCode) || IsKeyCodeLetter(uKeyCode) || uKeyCode == VK_ESCAPE;
    }

    [[nodiscard]] inline constexpr KeyCodes ConvertKeyCodeToNumber(const uintptr_t uKeyCode)
    {
		ASSERT(IsKeyCodeNumber(uKeyCode));
		return static_cast<KeyCodes>(static_cast<int>(KeyCodes::KEY_0) + (uKeyCode - StartNumberKeyCode));
    }

    [[nodiscard]] inline constexpr KeyCodes ConvertKeyCodeToLetter(const uintptr_t uKeyCode)
    {
        ASSERT(IsKeyCodeLetter(uKeyCode));
        return static_cast<KeyCodes>(static_cast<int>(KeyCodes::KEY_A) + (uKeyCode - StartLetterKeyCode));
    }

    [[nodiscard]] inline constexpr KeyCodes ConvertKeyCode(const uintptr_t uKeyCode)
    {
		ASSERT(IsKeyCodeSupported(uKeyCode));

		if (IsKeyCodeLetter(uKeyCode))
		{
			return ConvertKeyCodeToLetter(uKeyCode);
		}
		else if (IsKeyCodeNumber(uKeyCode))
		{
			return ConvertKeyCodeToNumber(uKeyCode);
		}
		else if(uKeyCode == VK_ESCAPE)
		{
			return KeyCodes::KEY_ESCAPE;
		}
		else 
		{
			ASSERT(false);
			return KeyCodes::KEY_COUNT;
		}
    }
};
