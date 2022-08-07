#pragma once

//framework
#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Utils/ClassMacros.h"
#include "Framework/Utils/DebugMacros.h"

//game
#include "Game/Drawables/Cube.h"
#include "Game/Drawables/GridDrawable.h"

//std
#include <vector>

class CGrid
{
	NON_COPYABLE_CLASS(CGrid)

public:
	enum class eCollisionType : char
	{
		OBSTABCLE,
		CHARACTER,

		COUNT,
	};

public:
	CGrid();
	
	void Init();
	[[nodiscard]] bool IsCollidingWithObstacle(const int iX, const int iY) const;
	[[nodiscard]] bool IsCollidingWithObstacle(const int iCellIndex) const;
	[[nodiscard]] eCollisionType GetCollisionType(const int iCellIndex) const;
	[[nodiscard]] bool IsInsideGrid(const int iX, const int iY) const;

	[[nodiscard]] int GetCollisionsCount() const;
	[[nodiscard]] int GetXSize() const;
	[[nodiscard]] int GetYSize() const;
	[[nodiscard]] float GetCellSize() const;
	[[nodiscard]] int GetGridCellSize() const;
	void GetCellXYFromIndex(const int iIndex, int& rOutX, int& rOutY) const;
	[[nodiscard]] int GetIndexFromXY(const int iX, const int iY) const;
	[[nodiscard]] const DirectX::SimpleMath::Vector3& GetMin() const;
	[[nodiscard]] const DirectX::SimpleMath::Vector3& GetMax() const;
	[[nodiscard]] DirectX::SimpleMath::Vector3 GetCellCenter(const int iIndex) const;
	[[nodiscard]] DirectX::SimpleMath::Vector3 GetCellCenter(const int iX, const int iY) const;
	[[nodiscard]] int GetIndexFromPos(const DirectX::SimpleMath::Vector3& rPos) const;

	void UpdateCharacterCollision(const int iOldPos, const int iNewPos, const eCollisionType collision);
	void CollisionUpdateFromPicker(const int iIndex);
	void RemoveCollisionIfNeeded(const int iIndex);
	void RemoveAllCollision();

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
	float m_fCellSize = 0.f;
	int m_iXSize = 0;
	int m_iYSize = 0;
};

inline bool CGrid::IsCollidingWithObstacle(const int iCellIndex) const { return m_gridCells[iCellIndex] == eCollisionType::OBSTABCLE; }
inline CGrid::eCollisionType CGrid::GetCollisionType(const int iCellIndex) const { return m_gridCells[iCellIndex]; }
inline int CGrid::GetCollisionsCount() const { return static_cast<int>(m_collisionIndexes.size()); }
inline int CGrid::GetXSize() const { return m_iXSize; }
inline int CGrid::GetYSize() const { return m_iYSize; }
inline float CGrid::GetCellSize() const { return m_fCellSize; }
inline int CGrid::GetGridCellSize() const { return static_cast<int>(m_gridCells.size()); }
inline int CGrid::GetIndexFromXY(const int iX, const int iY) const { return (iY * m_iXSize) + iX; }
inline const DirectX::SimpleMath::Vector3& CGrid::GetMin() const { return m_vMin; }
inline const DirectX::SimpleMath::Vector3& CGrid::GetMax() const { return m_vMax; }

inline void CGrid::UpdateCharacterCollision(const int iOldPos, const int iNewPos, const eCollisionType collision)
{
    ASSERT(!IsCollidingWithObstacle(iOldPos));
    ASSERT(!IsCollidingWithObstacle(iNewPos));

    m_gridCells[iOldPos] = eCollisionType::COUNT;
    m_gridCells[iNewPos] = collision;
}

inline bool CGrid::IsInsideGrid(const int iX, const int iY) const
{
    return iX >= 0
        && iY >= 0
        && iX < GetXSize()
        && iY < GetYSize();
}

inline bool CGrid::IsCollidingWithObstacle(const int iX, const int iY) const
{
    const int iIndex = GetIndexFromXY(iX, iY);
    return IsCollidingWithObstacle(iIndex);
}

inline void CGrid::GetCellXYFromIndex(const int iIndex, int& rOutX, int& rOutY) const
{
    rOutX = iIndex % m_iXSize;
    rOutY = (iIndex - rOutX) / m_iXSize;
}

inline DirectX::SimpleMath::Vector3 CGrid::GetCellCenter(const int iIndex) const
{
    int iX, iY;
    GetCellXYFromIndex(iIndex, iX, iY);
    return GetCellCenter(iX, iY);
}

inline DirectX::SimpleMath::Vector3 CGrid::GetCellCenter(const int iX, const int iY) const
{
	DirectX::SimpleMath::Vector3 pos(0.f, 0.f, 0.f);
    const float fHalfCellSize = GetCellSize() * 0.5f;

    pos.x = m_vMin.x + (iX * GetCellSize()) + fHalfCellSize;
    pos.z = m_vMin.z + (iY * GetCellSize()) + fHalfCellSize;

    return pos;
}

inline int CGrid::GetIndexFromPos(const DirectX::SimpleMath::Vector3& rPos) const
{
    const int iX = static_cast<int>(rPos.x / GetCellSize());
    const int iY = static_cast<int>(rPos.z / GetCellSize());

    return GetIndexFromXY(iX, iY);
}
