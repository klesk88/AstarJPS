#pragma once

#include "Framework/Utils/ClassMacros.h"
#include "Framework/Utils/DebugMacros.h"

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

template<class Class>
class CSingleton
{
	NON_COPYABLE_CLASS(CSingleton)

public:
	explicit CSingleton(Class& rClass);
	~CSingleton();

	static Class* GetInstance();

private:
	static Class* m_pInstance;
};

//////////////////////////////////////////////////////////////////////////

template<class Class>
Class* CSingleton<Class>::m_pInstance = nullptr;

template<class Class>
CSingleton<Class>::CSingleton(Class& rClass)
{
	m_pInstance = &rClass;
}

template<class Class>
Class* CSingleton<Class>::GetInstance()
{
	ASSERT(m_pInstance != nullptr);
	return m_pInstance;
}

template<class Class>
CSingleton<Class>::~CSingleton()
{}
