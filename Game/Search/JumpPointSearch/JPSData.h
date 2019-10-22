#pragma once

#include <vector>

#include "../BaseNode.h"

class CSquare;
class CGrid;

namespace JPS
{
	class CJPSNode final : public Search::CBaseNode
	{
	public:
		CJPSNode(const int iIndex);

		void AddForcedNeighbour(const int iForcedNeighbourIdx);

		const std::vector<int>& GetForcedNeighbours() const { return m_forcedNeighboursIndexes; }

	private:
		std::vector<int> m_forcedNeighboursIndexes;

#if _DEBUG
	public:
		bool RenderImgui(const CGrid& rGrid, CSquare& rSquare) const override;

	private: 
		mutable bool m_bRenderForceNeigbours;
#endif
	};
}

