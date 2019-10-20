#pragma once

#include <vector>

#include "../../Framework/Engine/Core/SimpleMath.h"
#include "../../Framework/Utils/ClassMacros.h"
#include "../Drawables/Cube.h"
#include "../Drawables/GridDrawable.h"

class CGrid
{
	NON_COPYABLE_CLASS(CGrid)

public:
	enum eCollisionType : char
	{
		OBSTABCLE,
		CHARACTER,

		COUNT,
	};

public:
	CGrid();
	
	void Init();
	bool IsCollidingWithObstacle(const int iX, const int iY) const;
	bool IsCollidingWithObstacle(const int iCellIndex) const { return m_gridCells[iCellIndex] == eCollisionType::OBSTABCLE; }
	eCollisionType GetCollisionType(const int iCellIndex) const { return m_gridCells[iCellIndex]; }
	bool IsInsideGrid(const int iX, const int iY) const;

	int GetCollisionsCount() const { return (int)m_collisionIndexes.size(); }
	int GetXSize() const { return m_iXSize; }
	int GetYSize() const { return m_iYSize; }
	float GetCellSize() const { return m_fCellSize; }
	int GetGridCellSize() const { return (int)m_gridCells.size(); }
	void GetCellXYFromIndex(const int iIndex, int& rOutX, int& rOutY) const;
	int GetIndexFromXY(const int iX, const int iY) const { return (iY * m_iXSize) + iX; }
	const DirectX::SimpleMath::Vector3& GetMin() const { return m_vMin; }
	const DirectX::SimpleMath::Vector3& GetMax() const { return m_vMax; }
	DirectX::SimpleMath::Vector3 GetCellCenter(const int iIndex) const;
	DirectX::SimpleMath::Vector3 GetCellCenter(const int iX, const int iY) const;
	int GetIndexFromPos(const DirectX::SimpleMath::Vector3& rPos) const;

	void UpdateCharacterCollision(const int iOldPos, const int iNewPos, const eCollisionType collision);
	void CollisionUpdateFromPicker(const int iIndex);
	void RemoveCollisionIfNeeded(const int iIndex);

private:
	void AddDrawableObstacle(const int iIndex);
	void RemoveDrawableObstacle(const int iIndex);
	void UpdateCollisionDrawable();

private:
	CCube m_drawableCollision;
	CGridDrawable m_drawableGrid;
	std::vector<eCollisionType> m_gridCells;
	std::vector<int> m_collisionIndexes;
	DirectX::SimpleMath::Vector3 m_vMin;
	DirectX::SimpleMath::Vector3 m_vMax;
	float m_fCellSize;
	int m_iXSize;
	int m_iYSize;
};