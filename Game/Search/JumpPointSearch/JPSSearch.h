#pragma once

//Implementation of the Jump Point Search algorithm 
//based on the paper 
//http://users.cecs.anu.edu.au/~dharabor/data/papers/harabor-grastien-aaai11.pdf

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

		void Search();
		void FindNeighbours(CJPSNode& rNode, std::vector<CJPSNode>& rCells, std::vector<int>& rOutNewIndexes) const;

	private:
		void InternalHandleStartNode(CJPSNode& rNode, std::vector<CJPSNode>& rCells, std::vector<int>& rOutNewIndexes) const;

		bool IsNextValidForceNode(const int iX, const int iY) const;
		bool HasCollisionInPosition(const int iX, const int iY) const;
		//scan the line horizontally, vertically and diagonally, until we don t find a cell 
		//of interest in that direction. Cell of interest means that we can't reach it in any other way
		//in the direction we are scanning
		int ScanHorizontally(const int iNodeIndex, const int iDir, std::vector<CJPSNode>& rOutNewNode, std::vector<int>& rOutNewIndexes) const;
		int ScanVertically(const int iNodeIndex, const int iDir, std::vector<CJPSNode>& rOutNewNode, std::vector<int>& rOutNewIndexes) const;
		int ScanDiagonally(const int iNodeIndex, const int iXDir, const int iYDir, std::vector<CJPSNode>& rOutNewNode, std::vector<int>& rOutNewIndexes) const;

		bool ShouldStopScanning(const int iX, const int iY, const int iNodeIndex, const std::vector<CJPSNode>& rNodes, int& rOutIndex) const;
		void AddToNewIndexesListIfValid(const int iJumpNodeIdx, std::vector<int>& rOutNewIndexes) const;
	};
}