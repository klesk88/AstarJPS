#include "BaseNode.h"

#include <cfloat>

#if _DEBUG
#include <DirectXColors.h>

#include "../Drawables/Square.h"
#include "../Scenes/Grid.h"
#include "../../Framework/Engine/Core/SimpleMath.h"
#include "../../Framework/Utils/Imgui/imgui.h"

using namespace DirectX::SimpleMath;

#endif

namespace Search
{
	CBaseNode::CBaseNode(int iIndex)
		: m_iIndex(iIndex)
		, m_iParentIdx(-1)
		, m_fGScore(FLT_MAX)
		, m_fHScore(FLT_MAX)
		, m_bIsInOpenSet(false)
		, m_bIsInClosedSet(false)
	{}

	bool CBaseNode::HasBeenSearched() const
	{
		return m_fGScore != FLT_MAX;
	}

#if _DEBUG
	bool CBaseNode::RenderImgui(const CGrid& rGrid, CSquare& rSquare) const
	{
		if (!HasBeenSearched())
		{
			return false;
		}

		char nodeName[128];
		sprintf_s(nodeName, "%d", m_iIndex);
		if (!ImGui::CollapsingHeader(nodeName))
		{
			return false;
		}

		int iX, iY;
		rGrid.GetCellXYFromIndex(m_iIndex, iX, iY);
		ImGui::Text("X : %d, Y : %d", iX, iY);

		AddNodeToDrawListIfInSearch(rGrid, rSquare);

		if (m_iParentIdx != -1)
		{
			ImGui::Text("Parent index : %d", m_iParentIdx);
			rGrid.GetCellXYFromIndex(m_iParentIdx, iX, iY);
			ImGui::Text("Parent X : %d, Y : %d", iX, iY);
		}

		ImGui::Text("G Score %.3f", m_fGScore);
		ImGui::Text("H Score %.3f", m_fHScore);

		return true;
	}

	void CBaseNode::AddNodeToDrawListIfInSearch(const CGrid& rGrid, CSquare& rSquare) const
	{
		int iRight, iForward;
		rGrid.GetCellXYFromIndex(m_iIndex, iRight, iForward);
		ImGui::Text("X : %d, Y : %d", iRight, iForward);

		rSquare.AddSingleSquare(iRight, iForward, rGrid.GetCellSize(), Color(DirectX::Colors::Green));
	}

#endif
}