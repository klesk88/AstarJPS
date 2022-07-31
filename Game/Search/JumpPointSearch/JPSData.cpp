#include "Game/Search/JumpPointSearch/JPSData.h"

//framework
#include "Framework//Utils/DebugMacros.h"

//game
#include "Game/Scenes/Grid.h"
#include "Game/Drawables/Square.h"

//std
#include <queue>

#if _DEBUG
//framework
#include "Framework//Engine/Core/SimpleMath.h"
#include "Framework//Utils/Imgui/imgui.h"

//directx
#include <DirectXColors.h>

//std
#include <stdio.h>
#endif

using namespace DirectX::SimpleMath;
using namespace Search;

namespace JPS
{
	CJPSNode::CJPSNode(const int iIndex)
		: CBaseNode(iIndex)

	{
	}

	void CJPSNode::AddForcedNeighbour(const int iForcedNeighbourIdx)
	{
		ASSERT(GetIndex() != iForcedNeighbourIdx);
		ASSERT(std::find(m_forcedNeighboursIndexes.begin(), m_forcedNeighboursIndexes.end(), iForcedNeighbourIdx) == m_forcedNeighboursIndexes.end());

		m_forcedNeighboursIndexes.push_back(iForcedNeighbourIdx);
	}

#if _DEBUG

	bool CJPSNode::RenderImgui(const CGrid& rGrid, CSquare& rSquare) const
	{
		if (!CBaseNode::RenderImgui(rGrid, rSquare))
		{
			return false;
		}

		char nodeName[128];
		sprintf_s(nodeName, "Neighbours_%d", GetIndex());

		ImGui::Text("Forced Neighbors: %d", static_cast<int>(m_forcedNeighboursIndexes.size()));
		if (m_forcedNeighboursIndexes.size() > 0)
		{
			ImGui::Checkbox(nodeName, &m_bRenderForceNeigbours);

			if (m_bRenderForceNeigbours)
			{
				int iX, iY;
				for (const int iForceNeigh : m_forcedNeighboursIndexes)
				{
					rGrid.GetCellXYFromIndex(iForceNeigh, iX, iY);
					rSquare.AddSingleSquare(iX, iY, rGrid.GetCellSize(), Color(DirectX::Colors::Orange));
				}
			}
		}

		return true;
	}

#endif
}
