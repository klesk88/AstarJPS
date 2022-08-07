#pragma once

#include "Framework/Utils/ClassMacros.h"

class CInputKeyboardState;
class CInputMouseState;

//input class pass to the managers during the engine update which stores common data
class CManagerUpdateInput
{
    NON_COPYABLE_CLASS(CManagerUpdateInput)

public:
    explicit CManagerUpdateInput(const CInputKeyboardState& rKeyboardState, const CInputMouseState& rMouseState, const float fDeltaTime);
    ~CManagerUpdateInput() = default;

    [[nodiscard]] const CInputKeyboardState& GetKeyboardState() const;
    [[nodiscard]] const CInputMouseState& GetMouseState() const;
    [[nodiscard]] float GetDeltaTime() const;

private:
    const CInputKeyboardState& m_rKeyboardState;
    const CInputMouseState& m_rMouseState;
    float m_fDeltaTime = 0.f;
};

inline CManagerUpdateInput::CManagerUpdateInput(const CInputKeyboardState& rKeyboardState, const CInputMouseState& rMouseState, const float fDeltaTime)
    : m_rKeyboardState(rKeyboardState)
    , m_rMouseState(rMouseState)
    , m_fDeltaTime(fDeltaTime)
{
}

inline const CInputKeyboardState& CManagerUpdateInput::GetKeyboardState() const { return m_rKeyboardState; }
inline const CInputMouseState& CManagerUpdateInput::GetMouseState() const { return m_rMouseState;  }
inline float CManagerUpdateInput::GetDeltaTime() const { return m_fDeltaTime; }