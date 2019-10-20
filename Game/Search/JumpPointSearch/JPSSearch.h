#pragma once

#include "JPSData.h"
#include "../BaseSearchInput.h"

class CJPSNode;

namespace JPS
{

	//basic implementation of the Jump Point Search
	class CJPSInput final : public Search::CSearchInput<CJPSNode>
	{
	public:
		CJPSInput(const CGrid& rGrid, const int iStartLocation, const int iEndLocation, std::vector<int>& rOutPath DEBUG_ONLY(, CBaseSearchDebug<CJPSNode>& rOutDebug));

		void Search() override;
		void SetStartNode(CJPSNode& rStartNode) const override;
		void FindNeighbours(CJPSNode& rNode, std::vector<CJPSNode>& rCells, std::vector<int>& rOutNewIndexes) const override;

	private:
		void UpdateStartForcedNeighbours(const int iX, const int iY, CJPSNode& rOutStartNode) const;

		bool IsNextValidForceNode(const int iX, const int iY) const;
		bool HasCollisionInPosition(const int iX, const int iY) const;
		int ScanHorizontally(const int iNodeIndex, const int iDir, std::vector<CJPSNode>& rOutNewNode, std::vector<int>& rOutNewIndexes) const;
		int ScanVertically(const int iNodeIndex, const int iDir, std::vector<CJPSNode>& rOutNewNode, std::vector<int>& rOutNewIndexes) const;
		int ScanDiagonally(const int iNodeIndex, const int iXDir, const int iYDir, std::vector<CJPSNode>& rOutNewNode, std::vector<int>& rOutNewIndexes) const;

		bool ShouldStopScanning(const int iX, const int iY, const int iNodeIndex, const std::vector<CJPSNode>& rNodes, int& rOutIndex) const;
		void AddToNewIndexesListIfValid(const int iJumpNodeIdx, std::vector<int>& rOutNewIndexes) const;
	};
}