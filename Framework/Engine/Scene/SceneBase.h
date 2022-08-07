#pragma once

//base class for all scenes to extend
class CSceneBase
{
public:
	CSceneBase() = default;
	virtual ~CSceneBase() = default;

	virtual void Init();
	virtual void Shutdown() = 0;
	virtual void Update(const float fDeltaTimeSec) = 0;
};

inline void CSceneBase::Init() {}