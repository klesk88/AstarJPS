#pragma once

//this class make sure that the entity will remove itself from the entity updates
//when getting removed

class CEntity
{
public:
	CEntity();
	virtual ~CEntity();

	virtual void Update(const double dDeltaTime) = 0;

	int GetCellPosition() const { return m_iCellPosIndex; }
	void SetEnable(const bool bEnable);
	bool IsEnable() const { return m_bIsEnable; }

protected:
	virtual void OnEnable() {}
	virtual void OnDisable() {}

private:
	int m_iCellPosIndex;
	bool m_bIsEnable : 1;
};