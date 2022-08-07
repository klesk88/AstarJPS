#pragma once

//framework
#include "Framework/Utils/ClassMacros.h"

//std
#include <type_traits>

class CInputMessage
{
    NON_COPYABLE_CLASS(CInputMessage)

public:
    explicit CInputMessage(const uint32_t uMessage, const uintptr_t wParam, const intptr_t lParam);
    ~CInputMessage() = default;

    [[nodiscard]] uint32_t GetMessage() const;
    [[nodiscard]] uintptr_t GetWParam() const;
    [[nodiscard]] intptr_t GetLParam() const;
    
private:
    uint32_t m_uMessage = 0;
    uintptr_t m_wParam = 0;
    intptr_t m_lParam = 0;
};

inline CInputMessage::CInputMessage(const uint32_t uMessage, const uintptr_t wParam, const intptr_t lParam)
    : m_uMessage(uMessage)
    , m_wParam(wParam)
    , m_lParam(lParam)
{
}

inline uint32_t CInputMessage::GetMessage() const
{
    return m_uMessage;
}

inline uintptr_t CInputMessage::GetWParam() const
{
    return m_wParam;
}

inline intptr_t CInputMessage::GetLParam() const
{
    return m_lParam;
}