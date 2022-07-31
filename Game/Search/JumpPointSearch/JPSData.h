#pragma once

#include "Game/Search/BaseNode.h"

//std
#include <vector>

class CSquare;
class CGrid;

namespace JPS
{
	class CJPSNode final : public Search::CBaseNode
	{
	public:
		explicit CJPSNode(const int iIndex);
		~CJPSNode() = default;

		void AddForcedNeighbour(const int iForcedNeighbourIdx);
		[[nodiscard]] const std::vector<int>& GetForcedNeighbours() const { return m_forcedNeighboursIndexes; }

	private:
		std::vector<int> m_forcedNeighboursIndexes;

#if _DEBUG
	public:
		bool RenderImgui(const CGrid& rGrid, CSquare& rSquare) const override;

	private: 
		mutable bool m_bRenderForceNeigbours = false;
#endif
	};
}

