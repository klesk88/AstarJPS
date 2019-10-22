#pragma once

#include <functional>
#include <vector>

#include "../Helpers/Helpers.h"
#include "../../../Framework/Utils/DebugMacros.h"

#if _DEBUG
#include "BaseSearchDebug.h"
#endif

class CGrid;

namespace Search
{
	template<class NodeType>
	class CSearchInput
	{
	public:
		typedef std::function<float(const int iTargetX, const int iTargetY, const int iCurrentCellX, const int iCurrentCellY)> HFunc;
		HFunc m_ComputeHValueFunc;

	public:
		CSearchInput(const int iCellsPerIter, const CGrid& rGrid, const int iStartLocation, const int iEndLocation, std::vector<int>& rOutPath DEBUG_ONLY(, CBaseSearchDebug<NodeType>& rOutDebug));

		virtual void Search() = 0;
		virtual void FindNeighbours(NodeType& rNode, std::vector<NodeType>& rCells, std::vector<int>& rOutNewIndexes) const = 0;

		const CGrid& GetGrid() const { return m_rGrid; }
		int GetStartIndex() const { return m_iSrcIndex; }
		int GetTargetIndex() const { return m_iDestIndex; }
		int GetExpectedNewCellsCountPerIter() const { return m_iNewCellCountPerIter; }

	public:
		std::vector<int>& m_rOutPath;

	private:
		int m_iNewCellCountPerIter;
		const CGrid& m_rGrid;
		const int m_iSrcIndex;
		const int m_iDestIndex;

#if _DEBUG
	public:
		void SetDebug(const double dTime, const std::vector<NodeType>& rCells) { m_rDebug.Set(dTime, rCells, m_rOutPath, m_rGrid); }

	private:
		CBaseSearchDebug<NodeType>& m_rDebug;
#endif
	};

	//////////////////////////////////////////////////////////////////////////

	template<class NodeType>
	CSearchInput<NodeType>::CSearchInput(const int iCellsPerIter, const CGrid& rGrid, const int iStartLocation, const int iEndLocation, std::vector<int>& rOutPath DEBUG_ONLY(, CBaseSearchDebug<NodeType>& rOutDebug))
		: m_rGrid(rGrid)
		, m_iSrcIndex(iStartLocation)
		, m_iDestIndex(iEndLocation)
		, m_rOutPath(rOutPath)
		, m_iNewCellCountPerIter(iCellsPerIter)
		DEBUG_ONLY(, m_rDebug(rOutDebug))
	{
		m_ComputeHValueFunc = ([](const int iTargetX, const int iTargetY, const int iCurrentCellX, const int iCurrentCellY)->float {
			return Helpers::GetEuclideanDistance(iTargetX, iTargetY, iCurrentCellX, iCurrentCellY);
		});
	}
}