#pragma once

#include <DirectXColors.h>
#include <vector>

#include "ColorDrawableBase.h"
#include "../../Framework/Engine/Core/SimpleMath.h"

class CGrid;

class CLine final : public CColorDrawableBase
{
public:
	CLine();

	void AddLine(const DirectX::SimpleMath::Vector3& rStartPos, const DirectX::SimpleMath::Vector3& rEndPos, const DirectX::SimpleMath::Color color);
};