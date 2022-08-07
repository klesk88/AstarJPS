#pragma once 

//std
#include <cfloat>

class CGrid;
class CSquare;

namespace Search
{
	class CBaseNode
	{
	public:
		//iIndex is the cell index
		explicit CBaseNode(const int iIndex);
		~CBaseNode() = default;

		[[nodiscard]] bool HasBeenSearched() const;

		void SetParent(const int iIndex);
		void SetGScore(const float fGScore);
		void SetHScore(const float fHScore);
		void SetIsInOpenSet();
		void ClearIsInOpenSet();
		void SetInCloseSet();
		[[nodiscard]] bool IsInClosedSet() const;

		[[nodiscard]] int GetIndex() const;
		[[nodiscard]] int GetParentIndex() const;
		[[nodiscard]] float GetGScore() const;
		[[nodiscard]] float GetHScore() const;
		[[nodiscard]] bool IsInOpendSet() const;

		[[nodiscard]] float Getf() const;

	private:
        float m_fGScore = FLT_MAX;
        float m_fHScore = FLT_MAX;
		int m_iIndex = 0;
		int m_iParentIdx = -1;
		bool m_bIsInOpenSet = false;
		bool m_bIsInClosedSet = false;

#if _DEBUG
	public:
		virtual bool RenderImgui(const CGrid& rGrid, CSquare& rSquare) const;
		void AddNodeToDrawListIfInSearch(const CGrid& rGrid, CSquare& rSquare) const;
#endif
	};

    inline void CBaseNode::SetParent(const int iIndex) { m_iParentIdx = iIndex; }
    inline void CBaseNode::SetGScore(const float fGScore) { m_fGScore = fGScore; }
    inline void CBaseNode::SetHScore(const float fHScore) { m_fHScore = fHScore; }
    inline void CBaseNode::SetIsInOpenSet() { m_bIsInOpenSet = true; }
    inline void CBaseNode::ClearIsInOpenSet() { m_bIsInOpenSet = false; }
    inline void CBaseNode::SetInCloseSet() { m_bIsInClosedSet = true; }
    inline bool CBaseNode::IsInClosedSet() const { return m_bIsInClosedSet; }
    inline int CBaseNode::GetIndex() const { return m_iIndex; }
    inline int CBaseNode::GetParentIndex() const { return m_iParentIdx; }
    inline float CBaseNode::GetGScore() const { return m_fGScore; }
    inline float CBaseNode::GetHScore() const { return m_fHScore; }
    inline bool CBaseNode::IsInOpendSet() const { return m_bIsInOpenSet; }
    inline float CBaseNode::Getf() const { return m_fGScore + m_fHScore; }
    inline bool CBaseNode::HasBeenSearched() const { return m_fGScore != FLT_MAX; }
}