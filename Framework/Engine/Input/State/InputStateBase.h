#pragma once

//framework
#include "Framework/Engine/Input/Button/InputButton.h"
#include "Framework/Utils/ClassMacros.h"

//std
#include <vector>

class CInputMessage;

class CInputStateBase
{
    NON_COPYABLE_CLASS(CInputStateBase)

public:
    explicit CInputStateBase(const unsigned int iButtonCount);
    virtual ~CInputStateBase() = default;

    [[nodiscard]] virtual bool ProcessMessage(const CInputMessage& rMessage) = 0;
    virtual void EndFrame();

    void Update(const float fDeltaTime);

protected:
    //array containing the button states we are interested into
    std::vector<CInputButton> m_buttonsList;
};

inline void CInputStateBase::EndFrame() {}