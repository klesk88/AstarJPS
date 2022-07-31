#pragma once

//framework
#include "Framework/Engine/Core/SimpleMath.h"

//game
#include "Game/Drawables/ColorDrawableBase.h"

//directx
#include <DirectXColors.h>

//std
#include <vector>

class CGrid;

class CLine final : public CColorDrawableBase
{
public:
	CLine();
	~CLine() = default;

	void AddLine(const DirectX::SimpleMath::Vector3& rStartPos, const DirectX::SimpleMath::Vector3& rEndPos, const DirectX::SimpleMath::Color color);
};