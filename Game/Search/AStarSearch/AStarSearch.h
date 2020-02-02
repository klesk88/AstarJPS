#pragma once

#include "AStarNode.h"
#include "../BaseSearchInput.h"
#include "../../../Framework/Utils/DebugMacros.h"

namespace AStar
{
	class CAStarInput final : public Search::CSearchInput<CAStarNode>
	{
	private:
		enum eMovingDirection
		{
			UP = 0,
			LEFT,
			RIGHT,
			DOWN,
			UP_LEFT,
			UP_RIGHT,
			DOWN_LEFT,
			DOWN_RIGHT,
			COUNT
		};

	public:
		CAStarInput(const CGrid& rGrid, const int iStartLocation, const int iEndLocation, std::vector<int>& rOutPath DEBUG_ONLY(, CBaseSearchDebug<CAStarNode>& rOutDebug));

		void Search();
		void FindNeighbours(CAStarNode& rNode, std::vector<CAStarNode>& rCells, std::vector<int>& rOutNewIndexes) const;

	private:
		void GetMovingDirection(const eMovingDirection movingDirection, const int currentGridCell, int& rOutX, int& rOutY) const;
		bool IsCollidingWithObstacle(const eMovingDirection movingDirection, const int iX, const int iY, const int iXDir, const int iYDir) const;
	};
}