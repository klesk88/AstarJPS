#include "Framework/Engine/Input/KeyboardMouse/Keyboard/InputKeyboardState.h"

#include "Framework/Engine/Input/InputCommonIncludes.h"
#include "Framework/Engine/Input/InputMessage.h"
#include "Framework/Utils/Imgui/imgui.h"

CInputKeyboardState::CInputKeyboardState()
    : CInputStateBase(static_cast<unsigned int>(KeyboardKeyCodes::KeyCodes::KEY_COUNT))
{
}

void CInputKeyboardState::ProcessMessage(const CInputMessage& rMessage)
{
    if (ImGui::GetCurrentContext() && ImGui::GetIO().WantCaptureKeyboard)
    {
        return;
    }

    if (!KeyboardKeyCodes::IsKeyCodeSupported(rMessage.GetWParam()))
    {
        return;
    }

    const KeyboardKeyCodes::KeyCodes KeyCode = KeyboardKeyCodes::ConvertKeyCode(rMessage.GetWParam());
    switch (rMessage.GetMessage())
    {
    case WM_KEYUP:
    {
        m_buttonsList[static_cast<int>(KeyCode)].ClearIsPressed();
        break;
    }
    case WM_KEYDOWN:
    {
        m_buttonsList[static_cast<int>(KeyCode)].SetIsPressed();
        break;
    }
    default:
        break;
    }
}
