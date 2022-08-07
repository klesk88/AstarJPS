#pragma once

#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

//std
#include <utility>

namespace CollisionHelpers
{
	[[nodiscard]] constexpr bool IsRayIntersectingCube(const DirectX::SimpleMath::Vector3& rOrigin, const DirectX::SimpleMath::Vector3& rDir, const DirectX::SimpleMath::Vector3& rCubeMin, const DirectX::SimpleMath::Vector3& rCubeMax, float& rfOutDistance)
    {
        float tmin = (rCubeMin.x - rOrigin.x) / rDir.x;
        float tmax = (rCubeMax.x - rOrigin.x) / rDir.x;

        if (tmin > tmax)
        {
            std::swap(tmin, tmax);
        }

        float tymin = (rCubeMin.y - rOrigin.y) / rDir.y;
        float tymax = (rCubeMax.y - rOrigin.y) / rDir.y;

        if (tymin > tymax)
        {
            std::swap(tymin, tymax);
        }

        if ((tmin > tymax) || (tymin > tmax))
        {
            return false;
        }

        if (tymin > tmin)
        {
            tmin = tymin;
        }

        if (tymax < tmax)
        {
            tmax = tymax;
        }

        float tzmin = (rCubeMin.z - rOrigin.z) / rDir.z;
        float tzmax = (rCubeMax.z - rOrigin.z) / rDir.z;

        if (tzmin > tzmax)
        {
            std::swap(tzmin, tzmax);
        }

        if ((tmin > tzmax) || (tzmin > tmax))
        {
            return false;
        }

        if (tzmin > tmin)
        {
            tmin = tzmin;
        }

        if (tzmax < tmax)
        {
            tmax = tzmax;
        }

        rfOutDistance = tmin;
        return true;
    }
}