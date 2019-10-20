#include "Character.h"

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

void CCharacter::OnDisable()
{
	Clear();
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

	//set the position starting from the center again
	m_Position = m_rGrid.GetCellCenter(iNewPos);
	int iX, iY;
	m_rGrid.GetCellXYFromIndex(m_iCurrentPos, iX, iY);
	
	m_Cube.Clear();
	m_Cube.AddCube(iX, iY, m_rGrid.GetCellSize(), m_Color);
	m_Cube.Init(false);
}

int CCharacter::ComputeCurrentGridPos(const int iTargetCell, const float fDeltaTime)
{
	//compute the position of the cube based on the delta time. Make sure to don t overshoot
	//the node we need to currently reach.

	const Vector3 vTargetCellPos = m_rGrid.GetCellCenter(iTargetCell);
	const Vector3 vDist = vTargetCellPos - m_Position;
	Vector3 vDir = vDist;
	vDir.Normalize();
	
	float fDeltaOffset = fDeltaTime * m_fSpeed;
	const float fDistanceToTarget = Vector3::Distance(vTargetCellPos, m_Position);
	if (fDeltaOffset > fDistanceToTarget)
	{
		fDeltaOffset = fDistanceToTarget;
	}

	Vector3 vOffset = vDir * fDeltaOffset;
	m_Position += vOffset;

	return m_rGrid.GetIndexFromPos(m_Position);
}

