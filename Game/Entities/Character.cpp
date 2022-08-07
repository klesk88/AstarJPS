#include "Game/Entities/Character.h"

//framework
#include "Framework/Utils/DebugMacros.h"

//game
#include "Game/Helpers/Helpers.h"

using namespace DirectX::SimpleMath;

CCharacter::CCharacter(CGrid& rGrid, const CGrid::eCollisionType collisionType, const DirectX::XMVECTORF32 color)
	: m_rGrid(rGrid)
	, m_CollisionType(collisionType)
	, m_Color(color)
{
}

void CCharacter::Init(const int iStartIndex, const int iTargetPos)
{
	m_iCurrentPos = iStartIndex;
	int iX, iY;
	m_rGrid.GetCellXYFromIndex(iStartIndex, iX, iY);
	m_Cube.InitCube(iX, iY, m_rGrid.GetCellSize(), m_Color);
	m_Cube.Init();

	m_rGrid.UpdateCharacterCollision(m_iCurrentPos, m_iCurrentPos, m_CollisionType);
	m_Position = m_rGrid.GetCellCenter(iStartIndex);

	m_iTargetPos = iTargetPos;
	PerformSearch(iTargetPos);
}

void CCharacter::Clear()
{
	m_Cube.Reset();
	m_path.clear();
	m_iCurrentPos = -1;
}

void CCharacter::Update(const float fDeltaTimeSec)
{
	if (m_path.size() == 0)
	{
		return;
	}

	int iDesiredPos = m_path[m_path.size() - 1];
	const int iNewPos = ComputeCurrentGridPos(iDesiredPos);
	if (m_iCurrentPos == iNewPos)
	{
		return;
	}

	//if we reached the node of the path then remove it
	if (iNewPos == iDesiredPos)
	{
		m_path.pop_back();
	}

	m_rGrid.UpdateCharacterCollision(m_iCurrentPos, iNewPos, m_CollisionType);
	m_iCurrentPos = iNewPos;

	int iX, iY;
	m_rGrid.GetCellXYFromIndex(m_iCurrentPos, iX, iY);
	
	m_Cube.Reset();
	m_Cube.InitCube(iX, iY, m_rGrid.GetCellSize(), m_Color);
	m_Cube.Init();
}

int CCharacter::ComputeCurrentGridPos(const int iTargetCell)
{
	//compute the position of the cube based on the delta time. Make sure to don t overshoot
	//the node we need to currently reach.

	const Vector3 vTargetCellPos = m_rGrid.GetCellCenter(iTargetCell);
	const Vector3 vCurrentCellCenter = m_rGrid.GetCellCenter(m_iCurrentPos);
	const Vector3 vDist = vTargetCellPos - vCurrentCellCenter;
    int iOldX, iOldY;
    m_rGrid.GetCellXYFromIndex(m_iCurrentPos, iOldX, iOldY);
    int iXDir = 1;
    int iYDir = 1;
	if (vDist.x < 0.f)
	{
		iXDir = -1;
	}
	else if (vDist.x == 0.f)
	{
		iXDir = 0;
	}

    if (vDist.z < 0.f)
    {
		iYDir = -1;
    }
    else if (vDist.z == 0.f)
    {
		iYDir = 0;
    }
	
	m_Position = m_rGrid.GetCellCenter(m_rGrid.GetIndexFromXY(iOldX + iXDir, iOldY + iYDir));
	return m_rGrid.GetIndexFromPos(m_Position);
}

