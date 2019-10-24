#include "Helpers.h"

#include <cmath>
#include <cstdlib>

#include "../Scenes/Grid.h"

namespace Helpers
{
	float GetEuclideanDistance(const int iCurrentX, const int iCurrentY, const int iTargetX, const int iTargetY)
	{
		const int dx = iTargetX - iCurrentX;
		const int dy = iTargetY - iCurrentY;
		return (float)(std::sqrt((dx * dx) + (dy * dy)));
	}

	float GetEuclideanDistance(const int iFirstIndex, const int iSecondIndex, const CGrid& rGrid)
	{
		int iX, iY;
		rGrid.GetCellXYFromIndex(iFirstIndex, iX, iY);
		int iSecondX, iSecondY;
		rGrid.GetCellXYFromIndex(iSecondIndex, iSecondX, iSecondY);

		return GetEuclideanDistance(iX, iY, iSecondX, iSecondY);
	}

	float ManhattanDistance(const int iCurrentX, const int iCurrentY, const int iTargetX, const int iTargetY)
	{
		return (float)(std::abs(iTargetX - iCurrentX) + std::abs(iTargetY - iCurrentY));
	}

	int Sign(float x)
	{
		return (x > 0.f) - (x < 0.f);
	}
}