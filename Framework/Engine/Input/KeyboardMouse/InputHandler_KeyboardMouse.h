#pragma once

//framework
#include "Framework/Engine/Input/InputHandlerBase.h"
#include "Framework/Engine/Input/KeyboardMouse/Keyboard/InputKeyboardState.h"
#include "Framework/Engine/Input/KeyboardMouse/Mouse//InputMouseState.h"
#include "Framework/Utils/ClassMacros.h"

//std
#include <vector>

class CInputMessage;

class CInputHandler_KeyboardMouse final : public CInputHandlerBase
{
    NON_COPYABLE_CLASS(CInputHandler_KeyboardMouse)

public:
    CInputHandler_KeyboardMouse() = default;
    ~CInputHandler_KeyboardMouse() = default;

    //CInputHandlingBase
    void Initialize() override;
    void Shutdown() override;

    void ProcessMessage(const CInputMessage& rMessage) override;
    void Update(const float fDeltaTime) override;
    void EndFrame() override;

    [[nodiscard]] InputHandleTypes::Types GetType() const override;
    //CInputHandlingBase

    [[nodiscard]] const CInputKeyboardState& GetKeyboardState() const;
    [[nodiscard]] const CInputMouseState& GetMouseState() const;

private:
    CInputKeyboardState m_keyboardState;
    CInputMouseState m_mouseState;
};

inline InputHandleTypes::Types CInputHandler_KeyboardMouse::GetType() const { return InputHandleTypes::Types::KEYBOARDMOUSE; }
inline const CInputKeyboardState& CInputHandler_KeyboardMouse::GetKeyboardState() const { return m_keyboardState; }
inline const CInputMouseState& CInputHandler_KeyboardMouse::GetMouseState() const { return m_mouseState; }