#pragma once

#include "Character.h"
#include "../Search/AStarSearch/AStarNode.h"

#if _DEBUG
#include "../Search/BaseSearchDebug.h"
#endif

namespace AStar
{
	class CAStarNode;
}

class CAStarCharacter final : public CCharacter
{
public:
	CAStarCharacter(CGrid& rGrid);

	void Init(const int iStartCell, const int iTargetPos) override;
	void Clear() override;

private:
	void PerformSearch(const int iTargetLocation) override;

#if _DEBUG
public:
	void UpdateImgui() override;

private:
	CBaseSearchDebug<AStar::CAStarNode> m_searchDebug;
#endif
};