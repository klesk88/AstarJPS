#pragma once

//framework
#include "Framework/Utils/ClassMacros.h"
#include "Framework/Utils/DebugMacros.h"

class CInputButton
{
    NON_COPYABLE_CLASS(CInputButton)

private:
    enum class eButtonState : char
    {
        START_HELD = 0,
        HELD,
        RELEASED_THIS_FRAME,
        RELEASED,
        
        COUNT
    };

public:
    CInputButton() = default;
    ~CInputButton() = default;

    void Update(const float fDeltaTime);

    [[nodiscard]] bool IsPressed() const;
    void SetIsPressed();
    void ClearIsPressed();

    [[nodiscard]] bool IsHeld() const;
    [[nodiscard]] float GetHoldTime() const;
    [[nodiscard]] bool WasPressedThisFrame() const;

private:
    //time the button has been old in seconds
    float m_fHoldTime = 0.f;
    eButtonState m_buttonState = eButtonState::COUNT;
};

inline bool CInputButton::IsPressed() const { return m_buttonState == eButtonState::HELD; }
inline void CInputButton::SetIsPressed() { m_buttonState = eButtonState::START_HELD; }
inline void CInputButton::ClearIsPressed() { m_buttonState = eButtonState::RELEASED; }
inline bool CInputButton::IsHeld() const 
{ 
    ASSERT(m_fHoldTime == 0.f || IsPressed());  
    return m_fHoldTime != 0.f; 
}

inline float CInputButton::GetHoldTime() const { return m_fHoldTime; }
inline bool CInputButton::WasPressedThisFrame() const { return m_buttonState == eButtonState::RELEASED_THIS_FRAME; }