#pragma once

//framework
#include "Framework/Engine/Core/SimpleMath.h"

//game
#include "Game/Drawables/ColorDrawableBase.h"

//std
#include <utility>

class CGrid;

class CGridDrawable final : public CColorDrawableBase
{
public:
	CGridDrawable();
	~CGridDrawable() = default;

	void InitParams(const int iSizeX, const int iSizeY, const float fCellSize, DirectX::SimpleMath::Vector3&rOutMin, DirectX::SimpleMath::Vector3&rOutMax);

private:
	void AddSquareLines(const int iStartX, const int iStartY, const float fCellSize, const DirectX::SimpleMath::Color color);
};