#include "Character.h"

#include "../Helpers/Helpers.h"
#include "../../Framework/Utils/DebugMacros.h"

using namespace DirectX::SimpleMath;

CCharacter::CCharacter(CGrid& rGrid, const CGrid::eCollisionType collisionType, const DirectX::XMVECTORF32 color)
	: m_rGrid(rGrid)
	, m_iCurrentPos(0)
	, m_CollisionType(collisionType)
	, m_Color(color)
	, m_Position(0.f, 0.f, 0.f)
	, m_fSpeed(0.001f)
	, m_iTargetPos(-1)
{
#if _DEBUG
	m_bRenderPath = true;
#endif
}

void CCharacter::Init(const int iStartIndex, const int iTargetPos)
{
	m_iCurrentPos = iStartIndex;
	int iX, iY;
	m_rGrid.GetCellXYFromIndex(iStartIndex, iX, iY);
	m_Cube.AddCube(iX, iY, m_rGrid.GetCellSize(), m_Color);
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

void CCharacter::Update(const double dDeltaTime)
{
	if (m_path.size() == 0)
	{
		return;
	}

	int iDesiredPos = m_path[m_path.size() - 1];
	const int iNewPos = ComputeCurrentGridPos(iDesiredPos, (float)dDeltaTime);
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
	m_Cube.AddCube(iX, iY, m_rGrid.GetCellSize(), m_Color);
	m_Cube.Init();
}

int CCharacter::ComputeCurrentGridPos(const int iTargetCell, const float fDeltaTime)
{
	//compute the position of the cube based on the delta time. Make sure to don t overshoot
	//the node we need to currently reach.

	const Vector3 vTargetCellPos = m_rGrid.GetCellCenter(iTargetCell);
	const Vector3 vCurrentCellCenter = m_rGrid.GetCellCenter(m_iCurrentPos);
	const Vector3 vDist = vTargetCellPos - vCurrentCellCenter;
	Vector3 vDir = vDist;
	vDir.Normalize();
	
	const float fDeltaOffset = fDeltaTime * m_fSpeed;
	Vector3 vOffset = vDir * fDeltaOffset;
	m_Position += vOffset;

	const int iNewCellPos = m_rGrid.GetIndexFromPos(m_Position);
	if (iNewCellPos ==  m_iCurrentPos)
	{
		return m_rGrid.GetIndexFromPos(m_Position);
	}

	//make sure now that we are in the cell we expect if we change one
	//we can have rounding problems with small values which can cause us to jump
	//in the wrong cell adjacent to the one we want
	int iOldX, iOldY, iNewX, iNewY;
	m_rGrid.GetCellXYFromIndex(m_iCurrentPos, iOldX, iOldY);
	m_rGrid.GetCellXYFromIndex(iNewCellPos, iNewX, iNewY);
	const int iXDir = Helpers::Sign(vDir.x);
	const int iYDir = Helpers::Sign(vDir.z);
	iOldX += iXDir;
	iOldY += iYDir;
	m_Position = m_rGrid.GetCellCenter(m_rGrid.GetIndexFromXY(iOldX, iOldY));

	return m_rGrid.GetIndexFromPos(m_Position);
}

