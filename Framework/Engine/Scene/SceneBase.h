#pragma once

class CSceneBase
{
public:
	CSceneBase() = default;
	virtual ~CSceneBase() {}

	virtual void Update(const double dDeltaTime) = 0;
	virtual void Shutdown() = 0;
};