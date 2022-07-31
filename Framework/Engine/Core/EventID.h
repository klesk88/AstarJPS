#pragma once

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

namespace EventIdHelper
{
    static constexpr int m_iInvalid = -1;
}

struct CEventId
{
public:
    CEventId();
    explicit CEventId(const int id);
    ~CEventId() = default;
 
    [[nodiscard]] static CEventId GetInvalidID();

    [[nodiscard]] bool operator<(const CEventId& other) const;
    [[nodiscard]] bool IsValid() const;

private:
    int m_iId;
};

inline CEventId::CEventId() 
    : m_iId(EventIdHelper::m_iInvalid) 
{}

inline CEventId::CEventId(const int id) 
    : m_iId(id) 
{}

inline CEventId CEventId::GetInvalidID() { return CEventId(EventIdHelper::m_iInvalid); }
inline bool CEventId::operator<(const CEventId& other) const { return m_iId < other.m_iId; }
inline bool CEventId::IsValid() const { return m_iId != EventIdHelper::m_iInvalid; }