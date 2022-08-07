#pragma once

//framework
#include "Framework/Engine/Input/InputHandlerTypes.h"
#include "Framework/Utils/ClassMacros.h"

class CInputMessage;

class CInputHandlerBase
{
    NON_COPYABLE_CLASS(CInputHandlerBase)

public:
    CInputHandlerBase() = default;
    virtual ~CInputHandlerBase() = default;

    virtual void Initialize() = 0;
    virtual void Shutdown() = 0;

    // process the input messages we receive from the OS
    [[nodiscard]] virtual bool ProcessMessage(const CInputMessage& rMessage) = 0;
    virtual void Update(const float fDeltaTime) = 0;
    //called at the end of the frame after all systems have been updated.
    //Can be used for example to remove data that was valid only during that frame
    virtual void EndFrame() = 0;

    [[nodiscard]] virtual InputHandleTypes::Types GetType() const = 0;
};