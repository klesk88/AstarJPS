#include "Game/Search/JumpPointSearch/JPSSearch.h"

//framework
#include "Framework//Utils/DebugMacros.h"

//game
#include "Game/Scenes/Grid.h"
#include "Game/Search/CommonSearchFunc.h"
#include "Game/Helpers/Helpers.h"

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
			rOutIndex = iNodeIndex;
			return true;
		}

		return false;
	}

	int CJPSInput::ScanHorizontally(const int iNodeIndex, const int iDir, std::vector<CJPSNode>& rOutNodes) const
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

			bool bForceNode = false;
			int iYForcePosDir = 1;
			//if we find a collision on above us then this is a force node. Make sure there is no obstacle which
			//would block the diagonal movement
			if (HasCollisionInPosition(iX, iY + iYForcePosDir) && IsNextValidForceNode(iX + iDir, iY) && IsNextValidForceNode(iX + iDir, iY + iYForcePosDir))
			{
				rNode.AddForcedNeighbour(rGrid.GetIndexFromXY(iX + iDir, iY + iYForcePosDir));
				bForceNode = true;
			}

			iYForcePosDir = -1;
			//if we find a collision on the bottom then this is a force node. Make sure there is no obstacle which
			//would block the diagonal movement
			if (HasCollisionInPosition(iX, iY + iYForcePosDir) && IsNextValidForceNode(iX + iDir, iY) && IsNextValidForceNode(iX + iDir, iY + iYForcePosDir))
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

	int CJPSInput::ScanVertically(const int iNodeIndex, const int iDir, std::vector<CJPSNode>& rOutNodes) const
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

			if (ShouldStopScanning(iX, iY, iCurrentCellIdx, rOutNodes, iIndexStop))
			{
				return iIndexStop;
			}

			CJPSNode& rNode = rOutNodes[iCurrentCellIdx];
			bool bForceNode = false;
			int iXForcePosDir = 1;
			//if we find a collision on the right then mark is as force. Make sure there is no obstacle which
			//would block the diagonal movement
			if (HasCollisionInPosition(iX + iXForcePosDir, iY) && IsNextValidForceNode(iX + iXForcePosDir, iY + iDir) && IsNextValidForceNode(iX, iY + iDir))
			{
				bForceNode = true;
				rNode.AddForcedNeighbour(rGrid.GetIndexFromXY(iX + iXForcePosDir, iY + iDir));
			}

			iXForcePosDir = -1;
			//if we find a collision on the left then mark is as force. Make sure there is no obstacle which
			//would block the diagonal movement
			if (HasCollisionInPosition(iX + iXForcePosDir, iY) && IsNextValidForceNode(iX + iXForcePosDir, iY + iDir) && IsNextValidForceNode(iX, iY + iDir))
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

	int CJPSInput::ScanDiagonally(const int iNodeIndex, const int iXDir, const int iYDir, std::vector<CJPSNode>& rOutNodes) const
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
			//make sure also that the cells on the side and on the bottom are not obstacles, if that is the case,
			//we could not have move here
			if (rGrid.IsInsideGrid(iX - iXDir, iY) && rGrid.IsCollidingWithObstacle(iX - iXDir, iY) && rGrid.IsInsideGrid(iX, iY - iYDir) && rGrid.IsCollidingWithObstacle(iX, iY - iYDir))
			{
				break;
			}

			if (ShouldStopScanning(iX, iY, iCurrentCellIdx, rOutNodes, iIndexStop))
			{
				return iIndexStop;
			}

			CJPSNode& rCurrentNode = rOutNodes[iCurrentCellIdx];

			bool bForceNode = false;
			bForceNode |= ScanHorizontally(iCurrentCellIdx, iXDir, rOutNodes) != -1;
			bForceNode |= ScanVertically(iCurrentCellIdx, iYDir, rOutNodes) != -1;

			//if we have an obstacle on our left then this is a forced node as we can´t reach it
			//from any other node. Make sure there is no obstacle which would block the diagonal movement
			if (HasCollisionInPosition(iX - iXDir, iY) && IsNextValidForceNode(iX - iXDir, iY + iYDir) && IsNextValidForceNode(iX, iY + iYDir))
			{
				rCurrentNode.AddForcedNeighbour(rGrid.GetIndexFromXY(iX - iXDir, iY + iYDir));
				bForceNode = true;
			}

			//obstacle at the bottom or top while going diagonally. Make sure there is no obstacle which
			//would block the diagonal movement
			if (HasCollisionInPosition(iX, iY - iYDir) && IsNextValidForceNode(iX + iXDir, iY - iYDir) && IsNextValidForceNode(iX + iXDir, iY))
			{
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
		//after that, if the node has any forced neighbor attached, go trough them. The start node 
		//is handle in a particular way as it doesnt have any parent direction but we need to check
		//all possible directions

		if (rNode.GetIndex() == GetStartIndex())
		{
			InternalHandleStartNode(rNode, rCells, rOutNewIndexes);
			return;
		}

		int iParentX, iParentY;
		GetGrid().GetCellXYFromIndex(rNode.GetParentIndex(), iParentX, iParentY);
		int iNodeX, iNodeY;
		GetGrid().GetCellXYFromIndex(rNode.GetIndex(), iNodeX, iNodeY);

		int iXDir = Helpers::clamp(iNodeX - iParentX, -1, 1);
		int iYDir = Helpers::clamp(iNodeY - iParentY, -1, 1);
		int iJumpNode = -1;
		if (iXDir != 0)
		{
			iJumpNode = ScanHorizontally(rNode.GetIndex(), iXDir, rCells);
			AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);
		}

		if (iYDir != 0)
		{
			iJumpNode = ScanVertically(rNode.GetIndex(), iYDir, rCells);
			AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);
		}

		if (iXDir != 0 && iYDir != 0)
		{
			iJumpNode = ScanDiagonally(rNode.GetIndex(), iXDir, iYDir, rCells);
			AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);
		}

		int iXNeigh, iYNeigh;

		for (const int iForcedNeighbour : rNode.GetForcedNeighbours())
		{
			GetGrid().GetCellXYFromIndex(iForcedNeighbour, iXNeigh, iYNeigh);
			iXDir = Helpers::clamp(iXNeigh - iNodeX, -1, 1);
			iYDir = Helpers::clamp(iYNeigh - iNodeY, -1, 1);

			iJumpNode = ScanDiagonally(rNode.GetIndex(), iXDir, iYDir, rCells);
			AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);
		}
	}

	void CJPSInput::InternalHandleStartNode(CJPSNode& rNode, std::vector<CJPSNode>& rCells, std::vector<int>& rOutNewIndexes) const
	{
		int iJumpNode = ScanHorizontally(rNode.GetIndex(), 1, rCells);
		AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);
		iJumpNode = ScanHorizontally(rNode.GetIndex(), -1, rCells);
		AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);

		iJumpNode = ScanVertically(rNode.GetIndex(), 1, rCells);
		AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);
		iJumpNode = ScanVertically(rNode.GetIndex(), -1, rCells);
		AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);

		iJumpNode = ScanDiagonally(rNode.GetIndex(), 1, 1, rCells);
		AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);
		iJumpNode = ScanDiagonally(rNode.GetIndex(), -1, 1, rCells);
		AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);

		iJumpNode = ScanDiagonally(rNode.GetIndex(), 1, -1, rCells);
		AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);
		iJumpNode = ScanDiagonally(rNode.GetIndex(), -1, -1, rCells);
		AddToNewIndexesListIfValid(iJumpNode, rOutNewIndexes);
	}

}