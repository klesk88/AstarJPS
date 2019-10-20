#include "AStarSearch.h"

#include "../CommonSearchFunc.h"
#include "../../Scenes/Grid.h"

using namespace Search;

namespace AStar
{
	CAStarInput::CAStarInput(const CGrid& rGrid, const int iStartLocation, const int iEndLocation, std::vector<int>& rOutPath DEBUG_ONLY(, CBaseSearchDebug<CAStarNode>& rOutDebug))
		: CSearchInput<CAStarNode>(8, rGrid, iStartLocation, iEndLocation, rOutPath DEBUG_ONLY(, rOutDebug))
	{}

	void CAStarInput::Search()
	{
		CommonSearch::Search<CAStarInput, CAStarNode>(*this);
	}

	void CAStarInput::FindNeighbours(CAStarNode& rNode, std::vector<CAStarNode>& rCells, std::vector<int>& rOutNewIndexes) const
	{
		ASSERT(rOutNewIndexes.size() == 0);

		int iNeigbourNodeX, iNeighbourNodeY;
		int iCurrentNodeX, iCurrentNodeY;
		GetGrid().GetCellXYFromIndex(rNode.GetIndex(), iCurrentNodeX, iCurrentNodeY);
		for (int dir = 0; dir < eMovingDirection::COUNT; ++dir)
		{
			GetMovingDirection(static_cast<eMovingDirection>(dir), rNode.GetIndex(), iNeigbourNodeX, iNeighbourNodeY);

			if (!GetGrid().IsInsideGrid(iNeigbourNodeX, iNeighbourNodeY))
			{
				continue;
			}

			if (IsCollidingWithObstacle((eMovingDirection)dir, iNeigbourNodeX, iNeighbourNodeY, iNeigbourNodeX - iCurrentNodeX, iNeighbourNodeY - iCurrentNodeY))
			{
				continue;
			}

			rOutNewIndexes.push_back(GetGrid().GetIndexFromXY(iNeigbourNodeX, iNeighbourNodeY));
		}
	}

	void CAStarInput::GetMovingDirection(const eMovingDirection movingDirection, const int currentGridCell, int& rOutX, int& rOutY) const
	{
		GetGrid().GetCellXYFromIndex(currentGridCell, rOutX, rOutY);
		switch (movingDirection)
		{
		case eMovingDirection::UP:
			rOutY++;
			break;
		case eMovingDirection::DOWN:
			rOutY--;
			break;
		case eMovingDirection::RIGHT:
			rOutX++;
			break;
		case eMovingDirection::LEFT:
			--rOutX;
			break;
		case eMovingDirection::COUNT:
			break;
		case eMovingDirection::UP_LEFT:
			rOutX--;
			rOutY++;
			break;
		case eMovingDirection::UP_RIGHT:
			rOutX++;
			rOutY++;
			break;
		case eMovingDirection::DOWN_LEFT:
			rOutX--;
			rOutY--;
			break;
		case eMovingDirection::DOWN_RIGHT:
			rOutX++;
			rOutY--;
			break;
		}
	}

	bool CAStarInput::IsCollidingWithObstacle(const eMovingDirection movingDirection, const int iX, const int iY, const int iXDir, const int iYDir) const
	{
		const CGrid& rGrid = GetGrid();
		switch (movingDirection)
		{
		case eMovingDirection::UP:
		case eMovingDirection::DOWN:
		case eMovingDirection::RIGHT:
		case eMovingDirection::LEFT:
		case eMovingDirection::COUNT:
			return rGrid.IsCollidingWithObstacle(iX, iY);
		case eMovingDirection::UP_LEFT:
		case eMovingDirection::UP_RIGHT:
		case eMovingDirection::DOWN_LEFT:
		case eMovingDirection::DOWN_RIGHT:
			return rGrid.IsCollidingWithObstacle(iX, iY) || (rGrid.IsCollidingWithObstacle(iX - iXDir, iY) && rGrid.IsCollidingWithObstacle(iX, iY - iYDir));
		}

		ASSERT(false);
		return false;
	}
}