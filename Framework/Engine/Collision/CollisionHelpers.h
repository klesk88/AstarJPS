#pragma once

#include "../Core/SimpleMath.h"

namespace CollisionHelpers
{
	bool IsRayIntersectingCube(const DirectX::SimpleMath::Vector3& rOrigin, const DirectX::SimpleMath::Vector3& rDir, const DirectX::SimpleMath::Vector3& rCubeMin, const DirectX::SimpleMath::Vector3& rCubeMax, float& rfOutDistance);
}