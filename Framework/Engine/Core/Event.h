#pragma once

#include "Framework/Engine/Core/EventID.h"
#include "Framework/Utils/ClassMacros.h"
#include "Framework/Utils/DebugMacros.h"

//std
#include <functional>
#include <map>

//base event and event handler class which are used as base
//classes for real events or by managers which need to handle
//events
template <typename... Args>
class CEventHandler
{
	NON_COPYABLE_CLASS(CEventHandler)

public:
	CEventHandler() = default;
	~CEventHandler();

	template <typename CallbackType>
	[[nodiscard]] CEventId Attach(CallbackType&& callback);

	template <typename C, typename R, typename... A >
	[[nodiscard]] CEventId Attach(C* object, R(C::* memFunc)(A...));

	void Detach(CEventId& id);

	void DetachAll();

	// calls all connected functions
	void Emit(const Args&... p);

private:
	std::map<CEventId, std::function<void(const Args&...)>> m_slots;
	int m_iCurrentId = EventIdHelper::m_iInvalid;
};

template <typename... Args>
CEventHandler<Args...>::~CEventHandler()
{
    ASSERT(m_slots.size() == 0);
}

template <typename... Args>
template <typename CallbackType>
inline CEventId CEventHandler<Args...>::Attach(CallbackType&& callback)
{
    m_slots.insert(std::make_pair(CEventId(++m_iCurrentId), std::forward<CallbackType>(callback)));
    return CEventId(m_iCurrentId);
}

template <typename... Args>
template <typename C, typename R, typename... A >
inline CEventId CEventHandler<Args...>::Attach(C* object, R(C::* memFunc)(A...))
{
    return Attach([object = object, memFunc = memFunc](Args... p) { (object->*(memFunc))(p...); });
}

template <typename... Args>
inline void CEventHandler<Args...>::Detach(CEventId& id)
{
    m_slots.erase(id);
    id = CEventId::GetInvalidID();
}

template <typename... Args>
inline void CEventHandler<Args...>::DetachAll()
{
    m_slots.clear();
}

template <typename... Args>
void CEventHandler<Args...>::Emit(const Args&... p)
{
    for (auto it : m_slots)
    {
        it.second(p...);
    }
}