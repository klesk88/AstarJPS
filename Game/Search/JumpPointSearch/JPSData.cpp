#include "JPSData.h"

#include <queue>

#include "../../../Framework/Utils/DebugMacros.h"

#include "../../Scenes/Grid.h"
#include "../../Drawables/Square.h"

#if _DEBUG
#include <DirectXColors.h>
#include <stdio.h>
#include "../../../Framework/Engine/Core/SimpleMath.h"
#include "../../../Framework/Utils/Imgui/imgui.h"
#endif

using namespace DirectX::SimpleMath;
using namespace Search;

namespace JPS
{
	CJPSNode::CJPSNode(const int iIndex)
		: CBaseNode(iIndex)

	{
#if _DEBUG
		m_bRenderForceNeigbours = false;
#endif
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

		ImGui::Text("Forced Neighbors: %d", (int)m_forcedNeighboursIndexes.size());
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
