#pragma once

//framework
#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

//game
#include "Game/Search/JumpPointSearch/JPSData.h"
#include "Game/Search/BaseSearchInput.h"

//std
#include <vector>

class CJPSNode;

namespace JPS
{

    //Implementation of the Jump Point Search algorithm 
	//based on the paper 
	//http://users.cecs.anu.edu.au/~dharabor/data/papers/harabor-grastien-aaai11.pdf

	class CJPSInput final : public Search::CSearchInput<CJPSNode>
	{
	public:
		explicit CJPSInput(const CGrid& rGrid, const int iStartLocation, const int iEndLocation, std::vector<int>& rOutPath DEBUG_ONLY(, CBaseSearchDebug<CJPSNode>& rOutDebug));
		~CJPSInput() = default;

		void Search();
		void FindNeighbours(CJPSNode& rNode, std::vector<CJPSNode>& rCells, std::vector<int>& rOutNewIndexes) const;

	private:
		void InternalHandleStartNode(CJPSNode& rNode, std::vector<CJPSNode>& rCells, std::vector<int>& rOutNewIndexes) const;

		[[nodiscard]] bool IsNextValidForceNode(const int iX, const int iY) const;
		[[nodiscard]] bool HasCollisionInPosition(const int iX, const int iY) const;
		//scan the line horizontally, vertically and diagonally, until we don t find a cell 
		//of interest in that direction. Cell of interest means that we can't reach it in any other way
		//in the direction we are scanning
		[[nodiscard]] int ScanHorizontally(const int iNodeIndex, const int iDir, std::vector<CJPSNode>& rOutNewNode, std::vector<int>& rOutNewIndexes) const;
		[[nodiscard]] int ScanVertically(const int iNodeIndex, const int iDir, std::vector<CJPSNode>& rOutNewNode, std::vector<int>& rOutNewIndexes) const;
		[[nodiscard]] int ScanDiagonally(const int iNodeIndex, const int iXDir, const int iYDir, std::vector<CJPSNode>& rOutNewNode, std::vector<int>& rOutNewIndexes) const;

		[[nodiscard]] bool ShouldStopScanning(const int iX, const int iY, const int iNodeIndex, const std::vector<CJPSNode>& rNodes, int& rOutIndex) const;
		void AddToNewIndexesListIfValid(const int iJumpNodeIdx, std::vector<int>& rOutNewIndexes) const;
	};

    inline void CJPSInput::AddToNewIndexesListIfValid(const int iJumpNodeIdx, std::vector<int>& rOutNewIndexes) const
    {
        if (iJumpNodeIdx == -1)
        {
            return;
        }

        rOutNewIndexes.push_back(iJumpNodeIdx);
    }

}