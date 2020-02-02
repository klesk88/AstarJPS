#pragma once

#include "ColorDrawableBase.h"
#include "../../Framework/Engine/Core/SimpleMath.h"

class CGrid;

class CSquare : public CColorDrawableBase
{
public:
	CSquare();

	void InitList(const std::vector<int>& indexes, const CGrid& rGrid, const DirectX::SimpleMath::Color color, const float fUpOffset = 0.1f);
	void AddSingleSquare(const int iStartX, const int iStartY, const float fCellSize, const DirectX::SimpleMath::Color& color);

private:
	void AddSquare(const int iStartX, const int iStartY, const float fCellSize, const DirectX::SimpleMath::Color color, const float fUpPffset);
};