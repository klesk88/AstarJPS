#pragma once

#include "Game/Scenes/Grid.h"

//std
#include <algorithm>
#include <cmath>
#include <cstdlib>

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

class CGrid;

namespace Helpers
{
    [[nodiscard]] inline float GetEuclideanDistance(const int iCurrentX, const int iCurrentY, const int iTargetX, const int iTargetY)
    {
        const int dx = iTargetX - iCurrentX;
        const int dy = iTargetY - iCurrentY;
        return static_cast<float>(std::sqrt((dx * dx) + (dy * dy)));
    }

	[[nodiscard]] inline float GetEuclideanDistance(const int iFirstIndex, const int iSecondIndex, const CGrid& rGrid)
	{
        int iX, iY;
        rGrid.GetCellXYFromIndex(iFirstIndex, iX, iY);
        int iSecondX, iSecondY;
        rGrid.GetCellXYFromIndex(iSecondIndex, iSecondX, iSecondY);

        return GetEuclideanDistance(iX, iY, iSecondX, iSecondY);
	}

    [[nodiscard]] inline float ManhattanDistance(const int iCurrentX, const int iCurrentY, const int iTargetX, const int iTargetY)
    {
        return static_cast<float>(std::abs(iTargetX - iCurrentX) + std::abs(iTargetY - iCurrentY));
    }

#undef max
#undef min
	template <typename T>
	[[nodiscard]] inline constexpr T clamp(const T& n, const T& lower, const T& upper)
	{
		return std::max(lower, std::min(n, upper));
	}
}
