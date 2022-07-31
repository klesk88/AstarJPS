#include "Game/Scenes/Grid.h"

//framework
#include "Framework/Utils/DebugMacros.h"

//directx
#include <DirectXColors.h>

using namespace DirectX::SimpleMath;

CGrid::CGrid()
	: m_fCellSize(0.f)
	, m_iXSize(0)
	, m_iYSize(0)
{}

void CGrid::Init()
{
	//initialize with something in the scene

	m_collisionIndexes = { 18, 25, 51, 52, 57, 59, 73, 83, 82, 96 };
	m_iXSize = 20;
	m_iYSize = 20;
	m_fCellSize = 0.5f;

	const int iTotalSize = m_iXSize * m_iYSize;

	m_gridCells.resize(iTotalSize, eCollisionType::COUNT);

	for (const int i : m_collisionIndexes)
	{
		m_gridCells[i] = eCollisionType::OBSTABCLE;
	}
	
	m_drawableCollision.InitList(m_collisionIndexes, *this, Color(DirectX::Colors::Black));
	m_drawableGrid.InitParams(m_iXSize, m_iYSize, m_fCellSize, m_vMin, m_vMax);
}

void CGrid::UpdateCharacterCollision(const int iOldPos, const int iNewPos, const eCollisionType collision)
{
	ASSERT(!IsCollidingWithObstacle(iOldPos));
	ASSERT(!IsCollidingWithObstacle(iNewPos));

	m_gridCells[iOldPos] = eCollisionType::COUNT;
	m_gridCells[iNewPos] = collision;
}

void CGrid::CollisionUpdateFromPicker(const int iIndex)
{
	if(IsCollidingWithObstacle(iIndex))
	{
		RemoveDrawableObstacle(iIndex);
	}
	else
	{ 
		AddDrawableObstacle(iIndex);
	}
}

void CGrid::RemoveCollisionIfNeeded(const int iIndex)
{
	if (!IsCollidingWithObstacle(iIndex))
	{
		return;
	}

	RemoveDrawableObstacle(iIndex);
}

void CGrid::RemoveAllCollision()
{
	for (int iIndex : m_collisionIndexes)
	{
		m_gridCells[iIndex] = eCollisionType::COUNT;
	}

	m_collisionIndexes.clear();
	UpdateCollisionDrawable();
}

void CGrid::AddDrawableObstacle(const int iIndex)
{
	std::vector<int>::iterator iter = std::find(m_collisionIndexes.begin(), m_collisionIndexes.end(), iIndex);
	if (iter != m_collisionIndexes.end())
	{
		return;
	}

	m_gridCells[iIndex] = eCollisionType::OBSTABCLE;
	m_collisionIndexes.push_back(iIndex);
	UpdateCollisionDrawable();
}

void CGrid::RemoveDrawableObstacle(const int iIndex)
{
	std::vector<int>::iterator iter = std::find(m_collisionIndexes.begin(), m_collisionIndexes.end(), iIndex);
	if (iter != m_collisionIndexes.end())
	{
		m_collisionIndexes.erase(iter);
	}
	
	m_gridCells[iIndex] = eCollisionType::COUNT;
	UpdateCollisionDrawable();
}

void CGrid::UpdateCollisionDrawable()
{
	if (m_collisionIndexes.size() == 0)
	{
		m_drawableCollision.Reset();
		return;
	}

	m_drawableCollision.InitList(m_collisionIndexes, *this, Color(DirectX::Colors::Black));
}
