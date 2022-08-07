#pragma once

//framework
#include "Framework/Engine/Input/KeyboardMouse/Keyboard/KeyboardKeyCodes.h"
#include "Framework/Engine/Input/State/InputStateBase.h"
#include "Framework/Utils/ClassMacros.h"

class CInputMessage;

class CInputKeyboardState final : public CInputStateBase
{
public:
    CInputKeyboardState();
    ~CInputKeyboardState() = default;

    //CInputStateBase
    void ProcessMessage(const CInputMessage& rMessage) override;
    //

    //return true if the button is currently pressed
    [[nodiscard]] bool IsPressed(const KeyboardKeyCodes::KeyCodes keyCode) const;
    //return true if the button was pressed in the previous frame, but in this frame we released it
    [[nodiscard]] bool WasPressed(const KeyboardKeyCodes::KeyCodes keyCode) const;
};

inline bool CInputKeyboardState::IsPressed(const KeyboardKeyCodes::KeyCodes keyCode) const
{
    ASSERT(keyCode != KeyboardKeyCodes::KeyCodes::KEY_COUNT);
    return m_buttonsList[static_cast<int>(keyCode)].IsPressed();
}

inline bool CInputKeyboardState::WasPressed(const KeyboardKeyCodes::KeyCodes keyCode) const
{
    ASSERT(keyCode != KeyboardKeyCodes::KeyCodes::KEY_COUNT);
    return m_buttonsList[static_cast<int>(keyCode)].WasPressedThisFrame();
}