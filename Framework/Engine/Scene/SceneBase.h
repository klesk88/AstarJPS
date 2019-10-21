#pragma once

class CSceneBase
{
public:
	CSceneBase()
		: m_bIsInUpdateList(false)
	{}

	virtual ~CSceneBase() {}

	virtual void Init() {}
	virtual void Shutdown() = 0;
	virtual void Update(const double dDeltaTime) = 0;

	bool IsInUpdateList() const { return m_bIsInUpdateList; }
	void SetInUpdateList() { m_bIsInUpdateList = true; }
	void ClearInUpdateList() { m_bIsInUpdateList = false; }

private:
	bool m_bIsInUpdateList : 1;
};