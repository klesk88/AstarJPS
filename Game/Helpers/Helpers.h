#pragma once

#include <algorithm>

class CGrid;

namespace Helpers
{
	float GetEuclideanDistance(const int iFirstIndex, const int iSecondIndex, const CGrid& rGrid);
	float GetEuclideanDistance(const int iCurrentX, const int iCurrentY, const int iTargetX, const int iTargetY);
	float ManhattanDistance(const int iCurrentX, const int iCurrentY, const int iTargetX, const int iTargetY);

#undef max
#undef min
	template <typename T>
	T clamp(const T& n, const T& lower, const T& upper)
	{
		return std::max(lower, std::min(n, upper));
	}
}
