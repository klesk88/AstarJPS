#include "Framework/Engine/Input/State/InputStateBase.h"

CInputStateBase::CInputStateBase(const unsigned int iButtonCount)
    : m_buttonsList(iButtonCount)
{}

void CInputStateBase::Update(const float fDeltaTime)
{
    for (CInputButton& rButton : m_buttonsList)
    {
        rButton.Update(fDeltaTime);
    }
}
