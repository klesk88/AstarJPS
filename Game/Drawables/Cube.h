#pragma once

#include <vector>

#include "ColorDrawableBase.h"
#include "../../Framework/Engine/Core/SimpleMath.h"

class CGrid;

class CCube final : public CColorDrawableBase
{
public:
	CCube();

	void InitList(const std::vector<int>& rIndexes, const CGrid& rGrid, const DirectX::SimpleMath::Color color);
	void AddCube(const int iStartX, const int iStartY, const float fCellSize, const DirectX::SimpleMath::Color color);
};