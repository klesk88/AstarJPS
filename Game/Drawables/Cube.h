#pragma once

//framework
#include "Framework/Engine/Core/SimpleMath.h"

//game
#include "Game/Drawables/ColorDrawableBase.h"

//std
#include <vector>

class CGrid;

class CCube final : public CColorDrawableBase
{
public:
	CCube();
	~CCube() = default;

	void InitList(const std::vector<int>& rIndexes, const CGrid& rGrid, const DirectX::SimpleMath::Color color);
	void AddCube(const int iStartX, const int iStartY, const float fCellSize, const DirectX::SimpleMath::Color color);
};