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
	//use a template class to express the base class that is used by the AStar and the
	//JPS search algorithm's. In this way we can express which type of data we want to 
	//use by each of them.
	//use also the curiously recurring template pattern to make sure the classes which will extend
	//this one will implement the Search and FindNeighbours methods.
	
	template<class NodeType>
	class CSearchInput
	{
	public:
		typedef std::function<float(const int iTargetX, const int iTargetY, const int iCurrentCellX, const int iCurrentCellY)> HFunc;
		HFunc m_ComputeHValueFunc;

	public:
		CSearchInput(const int iCellsPerIter, const CGrid& rGrid, const int iStartLocation, const int iEndLocation, std::vector<int>& rOutPath DEBUG_ONLY(, CBaseSearchDebug<NodeType>& rOutDebug));

		void Search();
		void FindNeighbours(NodeType& rNode, std::vector<NodeType>& rCells, std::vector<int>& rOutNewIndexes) const;

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

	template<class NodeType>
	void Search::CSearchInput<NodeType>::Search()
	{
		static_cast<NodeType*>(this)->Search();
	}

	template<class NodeType>
	void Search::CSearchInput<NodeType>::FindNeighbours(NodeType& rNode, std::vector<NodeType>& rCells, std::vector<int>& rOutNewIndexes) const
	{
		static_cast<NodeType*>(this)->FindNeighbours(rNode, rCells, rOutNewIndexes);
	}
}