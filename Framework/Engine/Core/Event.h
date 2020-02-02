#pragma once

//base event and event handler class which are used as base
//classes for real events or by managers which need to handle
//events

#include <functional>
#include <map>

#include "../../Utils/ClassMacros.h"
#include "../../Utils/DebugMacros.h"

namespace EventIdHelper
{
	const int m_iInvalid = -1;
}

struct CEventId
{
public:
	CEventId() : m_iId(EventIdHelper::m_iInvalid) {}
	explicit CEventId(const int id) : m_iId(id) {}

	static const CEventId Invalid() { return CEventId(EventIdHelper::m_iInvalid); }
	bool operator<(const CEventId& other) const { return m_iId < other.m_iId; }
	bool IsValid() const { return m_iId != EventIdHelper::m_iInvalid; }

private:
	int m_iId;
};

template <typename... Args>
class CEventHandler
{
	NON_COPYABLE_CLASS(CEventHandler)

public:
	CEventHandler()
		: m_iCurrentId(EventIdHelper::m_iInvalid)
	{}

	~CEventHandler()
	{
		ASSERT(m_slots.size() == 0);
	}

	template <typename A>
	CEventId Attach(A&& slot)
	{
		m_slots.insert(std::make_pair(CEventId(++m_iCurrentId), std::forward<A>(slot)));
		return CEventId(m_iCurrentId);
	}

	template <typename C, typename R, typename... A >
	CEventId Attach(C* object, R(C::* memFunc)(A...))
	{
		return Attach([object = object, memFunc = memFunc](Args... p) { (object->*(memFunc))(p...); });
	}

	void Detach(CEventId& id)
	{
		m_slots.erase(id);
		id = CEventId::Invalid();
	}

	void DetachAll()
	{
		m_slots.clear();
	}

	// calls all connected functions
	void Emit(const Args&... p)
	{
		for (auto it : m_slots)
		{
			it.second(p...);
		}
	}

private:
	std::map<CEventId, std::function<void(const Args&...)>> m_slots;
	int m_iCurrentId;
};