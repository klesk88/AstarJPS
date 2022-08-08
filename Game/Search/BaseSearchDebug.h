#pragma once

#if _DEBUG

//framework
#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Utils/Imgui/imgui.h"

//game
#include "Game/Scenes/Grid.h"
#include "Game/Drawables/Square.h"

//directx
#include <DirectXColors.h>

//std
#include <string.h>
#include <vector>

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
	std::shared_ptr<CSquare> m_drawableNode;
	std::shared_ptr<CSquare> m_drawablePath;
	std::shared_ptr<CSquare> m_drawableCompleteSearchSpace;
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
{
    m_drawableNode = std::make_shared<CSquare>();
    m_drawablePath = std::make_shared<CSquare>();
    m_drawableCompleteSearchSpace = std::make_shared<CSquare>();
}

template<class NodeType>
void CBaseSearchDebug<NodeType>::Set(const float fTimeMs, const std::vector<NodeType>& rSearchNodes, const std::vector<int>& rPath, const CGrid& rGrid)
{
	m_nodesInSearch = rSearchNodes;
	m_fTimeForSearch = fTimeMs;

	if (m_nodesInSearch.size() == 0)
	{
		m_drawablePath.get()->Reset();
	}
	else
	{
		m_drawablePath.get()->InitList(rPath, rGrid, m_color, 0.f);
		m_drawablePath.get()->RemoveFromRenderUpdate();
	}

	m_drawableCompleteSearchSpace.get()->Reset();
	for (const NodeType& rNode : rSearchNodes)
	{
		if (!rNode.HasBeenSearched())
		{
			continue;
		}

		rNode.AddNodeToDrawListIfInSearch(rGrid, *m_drawableCompleteSearchSpace.get());
		m_iNodesExpanded++;
	}

	if (m_iNodesExpanded == 0)
	{
		m_drawableCompleteSearchSpace.get()->Reset();
	}
	else
    {
        m_drawableCompleteSearchSpace.get()->Init();
		m_drawableCompleteSearchSpace.get()->RemoveFromRenderUpdate();
	}
}

template<class NodeType>
void CBaseSearchDebug<NodeType>::Clear()
{
	m_fTimeForSearch = 0.f;
	m_iNodesExpanded = 0;
	m_nodesInSearch.clear();
	m_drawableNode.get()->Reset();
	m_drawablePath.get()->Reset();
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
	m_drawableNode.get()->Reset();

	if (!ImGui::CollapsingHeader(m_imguiTreeName.c_str()))
	{
		return;
	}
	
	ImGui::PushID(this);

	ImGui::Text("Time took (ms):%.4f", m_fTimeForSearch);
	ImGui::Text("Nodes Expanded %d", m_iNodesExpanded);
	ImGui::Checkbox("Draw Path", &m_bDrawPath);
	ImGui::Checkbox("Draw All Searched Space", &m_bDrawAllSearchedSpace);

    CSquare* pDrawableNode = m_drawableNode.get();
	CSquare* pDrawablePath = m_drawablePath.get();
	CSquare* pDrawableSearchSpace = m_drawableCompleteSearchSpace.get();
    ASSERT(pDrawableNode != nullptr);
	ASSERT(pDrawablePath != nullptr);
	ASSERT(pDrawableSearchSpace != nullptr);

	DrawPathIfHasData(m_bDrawPath, *pDrawablePath);
	DrawPathIfHasData(m_bDrawAllSearchedSpace, *pDrawableSearchSpace);

	for (int i = 0; i < m_nodesInSearch.size(); ++i)
	{
		const NodeType& rNode = m_nodesInSearch[i];
		rNode.RenderImgui(rColission, *pDrawableNode);
	}

	if (!pDrawableNode->HasElementsToStoreInBuffer())
	{
		pDrawableNode->Reset();
	}
	else
	{
		pDrawableNode->Init();
	}

	ImGui::PopID();
}

#endif