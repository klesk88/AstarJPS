#pragma once

#if _DEBUG

#include <DirectXColors.h>
#include <vector>
#include <string.h>

#include "../Scenes/Grid.h"
#include "../Drawables/Square.h"
#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Utils/Imgui/imgui.h"

template<class NodeType>
class CBaseSearchDebug
{
public:
	explicit CBaseSearchDebug(const char* pName, const DirectX::XMVECTORF32& rColor);
	virtual ~CBaseSearchDebug() = default;

	void Set(const float fTimeMs, const std::vector<NodeType>& rSearchNodes, const std::vector<int>& rPath, const CGrid& rGrid);
	virtual void RenderImgui(const CGrid& rColission);
	void Clear();

private:
	void DrawPathIfHasData(const bool bShouldDraw, CSquare& rDrawable);

private:
	CSquare m_drawableNode;
	CSquare m_drawablePath;
	CSquare m_drawableCompleteSearchSpace;
	std::vector<NodeType> m_nodesInSearch;
	std::string m_imguiTreeName;
	float m_fTimeForSearch = 0.f;
	DirectX::SimpleMath::Color m_color;
	int m_iNodesExpanded = 0;
	bool m_bDrawPath = false;
	bool m_bDrawAllSearchedSpace = false;
};

template<class NodeType>
CBaseSearchDebug<NodeType>::CBaseSearchDebug(const char* pName, const DirectX::XMVECTORF32& rColor)
	: m_imguiTreeName(pName)
	, m_color(rColor)
{}

template<class NodeType>
void CBaseSearchDebug<NodeType>::Set(const float fTimeMs, const std::vector<NodeType>& rSearchNodes, const std::vector<int>& rPath, const CGrid& rGrid)
{
	m_nodesInSearch = rSearchNodes;
	m_fTimeForSearch = fTimeMs;

	if (m_nodesInSearch.size() == 0)
	{
		m_drawablePath.Reset();
	}
	else
	{
		m_drawablePath.InitList(rPath, rGrid, m_color, 0.f);
		m_drawablePath.RemoveFromRenderUpdate();
	}

	m_drawableCompleteSearchSpace.Reset();
	for (const NodeType& rNode : rSearchNodes)
	{
		if (!rNode.HasBeenSearched())
		{
			continue;
		}

		rNode.AddNodeToDrawListIfInSearch(rGrid, m_drawableCompleteSearchSpace);
		m_iNodesExpanded++;
	}

	if (m_iNodesExpanded == 0)
	{
		m_drawableCompleteSearchSpace.Reset();
	}
	else
	{
		m_drawableCompleteSearchSpace.Init();
		m_drawableCompleteSearchSpace.RemoveFromRenderUpdate();
	}
}

template<class NodeType>
void CBaseSearchDebug<NodeType>::Clear()
{
	m_fTimeForSearch = 0.f;
	m_iNodesExpanded = 0;
	m_nodesInSearch.clear();
	m_drawableNode.Reset();
	m_drawablePath.Reset();
}

template<class NodeType>
void CBaseSearchDebug<NodeType>::DrawPathIfHasData(const bool bShouldDraw, CSquare& rDrawable)
{
	if (!bShouldDraw)
	{
		rDrawable.RemoveFromRenderUpdate();
		return;
	}

	if (rDrawable.HasValidBuffer() && !rDrawable.IsInsideRenderUpdate())
	{
		rDrawable.AddToRenderUpdateIfNeeded();
	}
}

template<class NodeType>
void CBaseSearchDebug<NodeType>::RenderImgui(const CGrid& rColission)
{
	m_drawableNode.Reset();

	if (!ImGui::CollapsingHeader(m_imguiTreeName.c_str()))
	{
		return;
	}
	
	ImGui::PushID(this);

	ImGui::Text("Time took (ms):%.4f", m_fTimeForSearch);
	ImGui::Text("Nodes Expanded %d", m_iNodesExpanded);
	ImGui::Checkbox("Draw Path", &m_bDrawPath);
	ImGui::Checkbox("Draw All Searched Space", &m_bDrawAllSearchedSpace);

	DrawPathIfHasData(m_bDrawPath, m_drawablePath);
	DrawPathIfHasData(m_bDrawAllSearchedSpace, m_drawableCompleteSearchSpace);

	for (int i = 0; i < m_nodesInSearch.size(); ++i)
	{
		const NodeType& rNode = m_nodesInSearch[i];
		rNode.RenderImgui(rColission, m_drawableNode);
	}

	if (!m_drawableNode.HasElementsToStoreInBuffer())
	{
		m_drawableNode.Reset();
	}
	else
	{
		m_drawableNode.Init();
	}

	ImGui::PopID();
}

#endif