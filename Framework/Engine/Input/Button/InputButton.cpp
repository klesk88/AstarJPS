#include "Framework/Engine/Input/Button/InputButton.h"

void CInputButton::Update(const float fDeltaTime)
{
    switch (m_buttonState)
    {
    case eButtonState::START_HELD:
        m_buttonState = eButtonState::HELD;
        break;
    case eButtonState::HELD:
        m_fHoldTime += fDeltaTime;
        break;
    case eButtonState::RELEASED:
        m_buttonState = eButtonState::RELEASED_THIS_FRAME;
        break;
    case eButtonState::RELEASED_THIS_FRAME:
        m_buttonState = eButtonState::COUNT;
        m_fHoldTime = 0.f;
        break;
    case eButtonState::COUNT:
        break;
    }
}
