#pragma once

namespace EventIdHelper
{
    static constexpr int m_iInvalid = -1;
}

struct CEventId
{
public:
    CEventId() = default;
    explicit CEventId(const int id);
    ~CEventId() = default;
    
    [[nodiscard]] bool operator<(const CEventId& other) const;

    [[nodiscard]] static CEventId GetInvalidID();
    [[nodiscard]] bool IsValid() const;

private:
    int m_iId = EventIdHelper::m_iInvalid;
};

inline CEventId::CEventId(const int id) 
    : m_iId(id) 
{}

inline CEventId CEventId::GetInvalidID() { return CEventId(EventIdHelper::m_iInvalid); }
inline bool CEventId::operator<(const CEventId& other) const { return m_iId < other.m_iId; }
inline bool CEventId::IsValid() const { return m_iId != EventIdHelper::m_iInvalid; }