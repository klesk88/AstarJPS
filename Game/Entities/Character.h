#pragma once

#include <vector>

#include "../../Framework/Engine/Core/SimpleMath.h"
#include "../Drawables/Cube.h"
#include "../Scenes/Grid.h"

class CCharacter
{
public:
	CCharacter(CGrid& rGrid, const CGrid::eCollisionType collistionType, const DirectX::XMVECTORF32 color);
	virtual ~CCharacter() {}

	virtual void Update(const double dDeltaTime);

protected:
	virtual void PerformSearch(const int iTarget) = 0;

	virtual void Init(const int iStartIndex, const int iTargetPos);
	virtual void Clear();

private:
	int ComputeCurrentGridPos(const int iTargetCell, const float fDeltaTime);
	bool CanMoveAtCell(const int iCellIndex) const { return m_rGrid.IsCollidingWithObstacle(iCellIndex); }
	
protected:
	int m_iCurrentPos;
	CGrid& m_rGrid;
	std::vector<int> m_path;

private:
	CCube m_Cube;
	const CGrid::eCollisionType m_CollisionType;
	const DirectX::SimpleMath::Color m_Color;
	const float m_fSpeed;
	DirectX::SimpleMath::Vector3 m_Position;
	int m_iTargetPos;

#if _DEBUG
public:
	virtual void UpdateImgui() {}

protected:
	bool m_bRenderPath;
#endif
};