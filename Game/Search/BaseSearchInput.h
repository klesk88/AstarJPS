#pragma once

//framework
#include "Framework/Utils/DebugMacros.h"

//game
#include "Game/Helpers/Helpers.h"

//std
#include <functional>
#include <vector>

#if _DEBUG
#include "Game/Search/BaseSearchDebug.h"
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
		explicit CSearchInput(const int iCellsPerIter, const CGrid& rGrid, const int iStartLocation, const int iEndLocation, std::vector<int>& rOutPath DEBUG_ONLY(, CBaseSearchDebug<NodeType>& rOutDebug));
		~CSearchInput() = default;

		void Search();
		void FindNeighbours(NodeType& rNode, std::vector<NodeType>& rCells, std::vector<int>& rOutNewIndexes) const;

		[[nodiscard]] const CGrid& GetGrid() const;
		[[nodiscard]] int GetStartIndex() const;
		[[nodiscard]] int GetTargetIndex() const;
		[[nodiscard]] int GetExpectedNewCellsCountPerIter() const;

	public:
		std::vector<int>& m_rOutPath;

	private:
		const CGrid& m_rGrid;
		int m_iNewCellCountPerIter = 0;
		const int m_iSrcIndex = 0;
		const int m_iDestIndex = 0;

#if _DEBUG
	public:
		void SetDebug(const double dTime, const std::vector<NodeType>& rCells);

	private:
		CBaseSearchDebug<NodeType>& m_rDebug;
#endif
	};

	//////////////////////////////////////////////////////////////////////////

	template<class NodeType>
	CSearchInput<NodeType>::CSearchInput(const int iCellsPerIter, const CGrid& rGrid, const int iStartLocation, const int iEndLocation, std::vector<int>& rOutPath DEBUG_ONLY(, CBaseSearchDebug<NodeType>& rOutDebug))
		: m_rOutPath(rOutPath)
		, m_rGrid(rGrid)
		, m_iNewCellCountPerIter(iCellsPerIter)
		, m_iSrcIndex(iStartLocation)
		, m_iDestIndex(iEndLocation)
		DEBUG_ONLY(, m_rDebug(rOutDebug))
	{
		m_ComputeHValueFunc = ([](const int iTargetX, const int iTargetY, const int iCurrentCellX, const int iCurrentCellY)->float {
			return Helpers::GetEuclideanDistance(iTargetX, iTargetY, iCurrentCellX, iCurrentCellY);
		});
	}

	template<class NodeType>
	void CSearchInput<NodeType>::Search()
	{
		static_cast<NodeType*>(this)->Search();
	}

	template<class NodeType>
	void CSearchInput<NodeType>::FindNeighbours(NodeType& rNode, std::vector<NodeType>& rCells, std::vector<int>& rOutNewIndexes) const
	{
		static_cast<NodeType*>(this)->FindNeighbours(rNode, rCells, rOutNewIndexes);
	}

	template<class NodeType>
    inline const CGrid& CSearchInput<NodeType>::GetGrid() const { return m_rGrid; }
    
	template<class NodeType>
	inline int CSearchInput<NodeType>::GetStartIndex() const { return m_iSrcIndex; }
    
	template<class NodeType>
	inline int CSearchInput<NodeType>::GetTargetIndex() const { return m_iDestIndex; }
    
	template<class NodeType>
	inline int CSearchInput<NodeType>::GetExpectedNewCellsCountPerIter() const { return m_iNewCellCountPerIter; }

#if _DEBUG
	template<class NodeType>
    inline void CSearchInput<NodeType>::SetDebug(const double dTime, const std::vector<NodeType>& rCells) { m_rDebug.Set(dTime, rCells, m_rOutPath, m_rGrid); }
#endif
}