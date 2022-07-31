#pragma once

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

class CSceneBase
{
public:
	CSceneBase() = default;
	virtual ~CSceneBase() = default;

	virtual void Init();
	virtual void Shutdown() = 0;
	virtual void Update(const double dDeltaTime) = 0;
};

inline void CSceneBase::Init() {}