#include "JPSSearch.h"

#include "../CommonSearchFunc.h"
#include "../../Scenes/Grid.h"
#include "../../Helpers/Helpers.h"
#include "../../../Framework/Utils/DebugMacros.h"

using namespace Search;

namespace JPS
{
	CJPSInput::CJPSInput(const CGrid& rGrid, const int iStartLocation, const int iEndLocation, std::vector<int>& rOutPath DEBUG_ONLY(, CBaseSearchDebug<CJPSNode>& rOutDebug))
		: CSearchInput(40, rGrid, iStartLocation, iEndLocation, rOutPath DEBUG_ONLY(, rOutDebug))
	{}


	void CJPSInput::Search()
	{
		CommonSearch::Search<CJPSInput, CJPSNode>(*this);
	}

	bool CJPSInput::IsNextValidForceNode(const int iX, const int iY) const
	{
		return GetGrid().IsInsideGrid(iX, iY) && !GetGrid().IsCollidingWithObstacle(iX, iY);
	}

	void CJPSInput::SetStartNode(CJPSNode& rStartNode) const
	{
		//initialize the start node to have all the neighbors 
		//as forced neihgbours (if they are not a collision) sho we start the search.

		const CGrid& rGrid = GetGrid();

		const int iStartIndex = rStartNode.GetIndex();
		int iX, iY;
		rGrid.GetCellXYFromIndex(iStartIndex, iX, iY);

		UpdateStartForcedNeighbours(iX + 1, iY, rStartNode);
		UpdateStartForcedNeighbours(iX - 1, iY, rStartNode);
		UpdateStartForcedNeighbours(iX + 1, iY + 1, rStartNode);
		UpdateStartForcedNeighbours(iX - 1, iY + 1, rStartNode);
		UpdateStartForcedNeighbours(iX + 1, iY - 1, rStartNode);
		UpdateStartForcedNeighbours(iX - 1, iY - 1, rStartNode);
		UpdateStartForcedNeighbours(iX, iY - 1, rStartNode);
		UpdateStartForcedNeighbours(iX, iY + 1, rStartNode);
	}

	bool CJPSInput::HasCollisionInPosition(const int iX, const int iY) const
	{
		return GetGrid().IsInsideGrid(iX, iY) && GetGrid().IsCollidingWithObstacle(iX, iY);
	}

	bool CJPSInput::ShouldStopScanning(const int iX, const int iY, const int iNodeIndex, const std::vector<CJPSNode>& rNodes, int& rOutIndex) const
	{
		rOutIndex = -1;
		if (!GetGrid().IsInsideGrid(iX, iY))
		{
			return true;
		}

		if (GetGrid().IsCollidingWithObstacle(iX, iY))
		{
			return true;
		}

		if (GetGrid().GetIndexFromXY(iX, iY) == GetTargetIndex())
		{
			rOutIndex = GetTargetIndex();
			return true;
		}

		//the node has force neighbors we need to add it to the open list
		if (rNodes[iNodeIndex].GetForcedNeighbours().size() != 0)
		{
			return iNodeIndex;
		}

		return false;
	}

	int CJPSInput::ScanHorizontally(const int iNodeIndex, const int iDir, std::vector<CJPSNode>& rOutNodes, std::vector<int>& rOutNewIndexes) const
	{
		const CGrid& rGrid = GetGrid();
		int iX, iY;
		rGrid.GetCellXYFromIndex(iNodeIndex, iX, iY);
		ASSERT(iDir != 0 && (iDir == -1 || iDir == 1));

		int iIndexStop = -1;

		while (true)
		{
			iX += iDir;
			const int iCurrentCellIdx = rGrid.GetIndexFromXY(iX, iY);
			if (ShouldStopScanning(iX, iY, iCurrentCellIdx, rOutNodes, iIndexStop))
			{
				return iIndexStop;
			}

			CJPSNode& rNode = rOutNodes[iCurrentCellIdx];

			//this node has forced neigbours so add it to the open list
			if (rNode.GetForcedNeighbours().size() != 0)
			{
				rOutNewIndexes.push_back(iCurrentCellIdx);
				return iCurrentCellIdx;
			}

			bool bForceNode = false;
			int iYForcePosDir = 1;
			//if we find a collision on above us then this is a force node
			if (HasCollisionInPosition(iX, iY + iYForcePosDir) && IsNextValidForceNode(iX + iDir, iY + iYForcePosDir))
			{
				rNode.AddForcedNeighbour(rGrid.GetIndexFromXY(iX + iDir, iY + iYForcePosDir));
				bForceNode = true;
			}

			iYForcePosDir = -1;
			//if we find a collision on the bottom then this is a force node
			if (HasCollisionInPosition(iX, iY + iYForcePosDir) && IsNextValidForceNode(iX + iDir, iY + iYForcePosDir))
			{
				rNode.AddForcedNeighbour(rGrid.GetIndexFromXY(iX + iDir, iY + iYForcePosDir));
				bForceNode = true;
			}

			if (!bForceNode)
			{
				continue;
			}

			return iCurrentCellIdx;
		}

		return -1;
	}

	int CJPSInput::ScanVertically(const int iNodeIndex, const int iDir, std::vector<CJPSNode>& rOutNodes, std::vector<int>& rOutNewIndexes) const
	{
		const CGrid& rGrid = GetGrid();
		int iX, iY;
		rGrid.GetCellXYFromIndex(iNodeIndex, iX, iY);

		ASSERT(iDir != 0 && (iDir == -1 || iDir == 1));
		int iIndexStop = -1;

		while (true)
		{
			iY += iDir;
			const int iCurrentCellIdx = rGrid.GetIndexFromXY(iX, iY);

			if (ShouldStopScanning(iX, iY, iNodeIndex, rOutNodes, iIndexStop))
			{
				return iIndexStop;
			}

			CJPSNode& rNode = rOutNodes[iCurrentCellIdx];
			bool bForceNode = false;
			int iXForcePosDir = 1;
			//if we find a collision on the right then mark is as force
			if (HasCollisionInPosition(iX + iXForcePosDir, iY) && IsNextValidForceNode(iX + iXForcePosDir, iY + iDir))
			{
				bForceNode = true;
				rNode.AddForcedNeighbour(rGrid.GetIndexFromXY(iX + iXForcePosDir, iY + iDir));
			}

			iXForcePosDir = -1;
			//if we find a collision on the left then mark is as force
			if (HasCollisionInPosition(iX + iXForcePosDir, iY) && IsNextValidForceNode(iX + iXForcePosDir, iY + iDir))
			{
				bForceNode = true;
				rNode.AddForcedNeighbour(rGrid.GetIndexFromXY(iX + iXForcePosDir, iY + iDir));
			}

			if (!bForceNode)
			{
				continue;
			}

			return iCurrentCellIdx;
		}

		return -1;
	}

	int CJPSInput::ScanDiagonally(const int iNodeIndex, const int iXDir, const int iYDir, std::vector<CJPSNode>& rOutNodes, std::vector<int>& rOutNewIndexes) const
	{
		const CGrid& rGrid = GetGrid();
		int iX, iY;
		rGrid.GetCellXYFromIndex(iNodeIndex, iX, iY);

		ASSERT(iXDir != 0 && iYDir != 0);
		ASSERT(iXDir == 1 || iXDir == -1);
		ASSERT(iYDir == 1 || iYDir == -1);
		int iIndexStop = -1;

		while (true)
		{
			iX += iXDir;
			iY += iYDir;

			const int iCurrentCellIdx = rGrid.GetIndexFromXY(iX, iY);
			if (ShouldStopScanning(iX, iY, iCurrentCellIdx, rOutNodes, iIndexStop))
			{
				return iIndexStop;
			}

			CJPSNode& rCurrentNode = rOutNodes[iCurrentCellIdx];
			//now make sure also that the cells near us are not collision as, if that is the case,
			//we cant move there
			if (rGrid.IsCollidingWithObstacle(iX - iXDir, iY) && rGrid.IsCollidingWithObstacle(iX, iY - iYDir))
			{
				break;
			}

			int iJumpNodeIdx = -1;
			bool bForceNode = false;
			bForceNode |= ScanHorizontally(iCurrentCellIdx, iXDir, rOutNodes, rOutNewIndexes) != -1;
			bForceNode |= ScanVertically(iCurrentCellIdx, iYDir, rOutNodes, rOutNewIndexes) != -1;

			//if we have an obstacle on our left then this is a forced node as we can´t reach it
			//from any other node
			if (HasCollisionInPosition(iX + (iXDir * iYDir), iY) && IsNextValidForceNode(iX + (iXDir * iYDir), iY + iYDir))
			{
				ASSERT(iCurrentCellIdx != rGrid.GetIndexFromXY(iX + (iXDir * iYDir), iY + iYDir));
				rCurrentNode.AddForcedNeighbour(rGrid.GetIndexFromXY(iX + (iXDir * iYDir), iY + iYDir));
				bForceNode = true;
			}

			//obstacle at the bottom or top while going diagonally
			if (HasCollisionInPosition(iX, iY - iYDir) && IsNextValidForceNode(iX + (iXDir * iYDir), iY - iYDir))
			{
				ASSERT(iCurrentCellIdx != rGrid.GetIndexFromXY(iX + iXDir, iY - iYDir));
				rCurrentNode.AddForcedNeighbour(rGrid.GetIndexFromXY(iX + iXDir, iY - iYDir));
				bForceNode = true;
			}

			if (!bForceNode)
			{
				continue;
			}

			return iCurrentCellIdx;
		}

		return -1;
	}

	void CJPSInput::FindNeighbours(CJPSNode& rNode, std::vector<CJPSNode>& rCells, std::vector<int>& rOutNewIndexes) const
	{
		//check horizontally, vertically and diagonally from this node to see if we find any jump point.
		//after that, if the node has any forced neighbor attached, go trough them

		int iParentX, iParentY;
		GetGrid().GetCellXYFromIndex(rNode.GetParentIndex(), iParentX, iParentY);
		int iNodeX, iNodeY;
		GetGrid().GetCellXYFromIndex(rNode.GetIndex(), iNodeX, iNodeY);

		int iXDir = Helpers::clamp(iNodeX - iParentX, -1, 1);
		int iYDir = Helpers::clamp(iNodeY - iParentY, -1, 1);
		int iJumpNode = -1;
		if (iXDir != 0)
		{
			iJumpNode = ScanHorizontally(rNode.GetIndex(), iXDir, rCells, rOutNewIndexes);
			AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);
		}

		if (iYDir != 0)
		{
			iJumpNode = ScanVertically(rNode.GetIndex(), iYDir, rCells, rOutNewIndexes);
			AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);
		}

		if (iXDir != 0 && iYDir != 0)
		{
			iJumpNode = ScanDiagonally(rNode.GetIndex(), iXDir, iYDir, rCells, rOutNewIndexes);
			AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);
		}

		int iXNeigh, iYNeigh;
		for (const int iForcedNeighbour : rNode.GetForcedNeighbours())
		{
			GetGrid().GetCellXYFromIndex(iForcedNeighbour, iXNeigh, iYNeigh);
			iXDir = Helpers::clamp(iXNeigh - iNodeX, -1, 1);
			iYDir = Helpers::clamp(iYNeigh - iNodeY, -1, 1);

			iJumpNode = -1;
			if (iXDir != 0 && iYDir != 0)
			{
				iJumpNode = ScanDiagonally(rNode.GetIndex(), iXDir, iYDir, rCells, rOutNewIndexes);
			}
			else if(iXDir != 0)
			{
				iJumpNode = ScanHorizontally(rNode.GetIndex(), iXDir, rCells, rOutNewIndexes);
			}
			else
			{
				iJumpNode = ScanVertically(rNode.GetIndex(), iYDir, rCells, rOutNewIndexes);
			}

			AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);
		}
	}

	void CJPSInput::UpdateStartForcedNeighbours(const int iX, const int iY, CJPSNode& rOutStartNode) const
	{
		if (!IsNextValidForceNode(iX, iY))
		{
			return;
		}

		const int iIndex = GetGrid().GetIndexFromXY(iX, iY);
		ASSERT(rOutStartNode.GetIndex() != iIndex);
		rOutStartNode.AddForcedNeighbour(iIndex);
	}

	void CJPSInput::AddToNewIndexesListIfValid(const int iJumpNodeIdx, std::vector<int>& rOutNewIndexes) const
	{
		if (iJumpNodeIdx == -1)
		{
			return;
		}

		rOutNewIndexes.push_back(iJumpNodeIdx);
	}

}