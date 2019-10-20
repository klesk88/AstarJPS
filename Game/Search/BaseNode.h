#pragma once 

class CGrid;
class CSquare;

namespace Search
{
	class CBaseNode
	{
	public:
		CBaseNode(int iIndex);

		bool HasBeenSearched() const;

		void SetParent(const int iIndex) { m_iParentIdx = iIndex; }
		void SetGScore(const float fGScore) { m_fGScore = fGScore; }
		void SetHScore(const float fHScore) { m_fHScore = fHScore; }
		void SetIsInOpenSet() { m_bIsInOpenSet = true; }
		void ClearIsInOpenSet() { m_bIsInOpenSet = false; }
		void SetInCloseSet() { m_bIsInClosedSet = true; }
		bool IsInClosedSet() const { return m_bIsInClosedSet; }

		int GetIndex() const { return m_iIndex; }
		int GetParentIndex() const { return m_iParentIdx; }
		float GetGScore() const { return m_fGScore; }
		float GetHScore() const { return m_fHScore; }
		bool IsInOpendSet() const { return m_bIsInOpenSet; }

		float Getf() const { return m_fGScore + m_fHScore; }

	private:
		int m_iIndex;
		int m_iParentIdx;
		float m_fGScore;
		float m_fHScore;
		bool m_bIsInOpenSet : 1;
		bool m_bIsInClosedSet : 1;

#if _DEBUG
	public:
		virtual bool RenderImgui(const CGrid& rGrid, CSquare& rSquare) const;
		void AddNodeToDrawListIfInSearch(const CGrid& rGrid, CSquare& rSquare) const;
#endif
	};
}