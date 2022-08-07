#pragma once

//framework
#include "Framework/Engine/Core/SimpleMath.h"

//game
#include "Game/Drawables/Cube.h"
#include "Game/Scenes/Grid.h"

//directx
#include <directxmath.h>

//std
#include <vector>


#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

class CCharacter
{
public:
	explicit CCharacter(CGrid& rGrid, const CGrid::eCollisionType collistionType, const DirectX::XMVECTORF32 color);
	virtual ~CCharacter() = default;

	virtual void Update(const float fDeltaTimeSec);

protected:
	virtual void PerformSearch(const int iTarget) = 0;

	virtual void Init(const int iStartIndex, const int iTargetPos);
	virtual void Clear();

private:
	[[nodiscard]] int ComputeCurrentGridPos(const int iTargetCell);
	[[nodiscard]] bool CanMoveAtCell(const int iCellIndex) const { return m_rGrid.IsCollidingWithObstacle(iCellIndex); }
	
protected:
	int m_iCurrentPos = 0;
	CGrid& m_rGrid;
	std::vector<int> m_path;

private:
	CCube m_Cube;
	const CGrid::eCollisionType m_CollisionType = CGrid::eCollisionType::COUNT;
	const DirectX::SimpleMath::Color m_Color;
	static constexpr float m_fSpeed = 0.1f;
	DirectX::SimpleMath::Vector3 m_Position;
	int m_iTargetPos = -1;

#if _DEBUG
public:
	virtual void UpdateImgui() {}

protected:
	bool m_bRenderPath = true;
#endif
};