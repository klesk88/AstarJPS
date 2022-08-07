#pragma once

//framework
#include "Framework/Engine/Input/KeyboardMouse/Mouse/MouseKeyCodes.h"
#include "Framework/Engine/Input/State/InputStateBase.h"
#include "Framework/Utils/ClassMacros.h"
#include "Framework/Utils/DebugMacros.h"

class CInputMessage;

class CInputMouseState final : public CInputStateBase
{
    NON_COPYABLE_CLASS(CInputMouseState)

public:
    CInputMouseState();
    ~CInputMouseState() = default;

    //CInputStateBase
    [[nodiscard]] bool ProcessMessage(const CInputMessage& rMessage) override;
    void EndFrame() override;
    //CInputStateBase

    //return true if the button is currently pressed
    [[nodiscard]] bool IsPressed(const MouseKeyCodes::KeyCodes keyCode) const;
    //return true if the button was pressed in the previous frame, but in this frame we released it
    [[nodiscard]] bool WasPressed(const MouseKeyCodes::KeyCodes keyCode) const;

    [[nodiscard]] float GetPosDeltaXThisFrame() const;
    [[nodiscard]] float GetPosDeltaYThisFrame() const;
    [[nodiscard]] bool HasPositonDelta () const;
    [[nodiscard]] float GetWheelDelta() const;
    [[nodiscard]] int GetMousePositionX() const;
    [[nodiscard]] int GetMousePositionY() const;

private:
    void HandleRawInput(const CInputMessage& rMessage);

private:
    float m_fMouseWheelDelta = 0.f;
    float m_fPosDeltaXThisFrame = 0.f;
    float m_fPosDeltaYThisFrame = 0.f;
    int m_iPosX = 0;
    int m_iPosY = 0;
    bool m_bHasFocus = false;
};

inline bool CInputMouseState::IsPressed(const MouseKeyCodes::KeyCodes keyCode) const
{
    ASSERT(keyCode != MouseKeyCodes::KeyCodes::KEY_COUNT);
    return m_buttonsList[static_cast<int>(keyCode)].IsPressed();
}

inline bool CInputMouseState::WasPressed(const MouseKeyCodes::KeyCodes keyCode) const
{
    ASSERT(keyCode != MouseKeyCodes::KeyCodes::KEY_COUNT);
    return m_buttonsList[static_cast<int>(keyCode)].WasPressedThisFrame();
}

inline float CInputMouseState::GetPosDeltaXThisFrame() const { return m_fPosDeltaXThisFrame; }
inline float CInputMouseState::GetPosDeltaYThisFrame() const { return m_fPosDeltaYThisFrame; }
inline bool CInputMouseState::HasPositonDelta() const { return m_fPosDeltaXThisFrame != 0.f || m_fPosDeltaYThisFrame == 0.f; }
inline float CInputMouseState::GetWheelDelta() const { return m_fMouseWheelDelta; }
inline int CInputMouseState::GetMousePositionX() const { return m_iPosX; }
inline int CInputMouseState::GetMousePositionY() const { return m_iPosY; }