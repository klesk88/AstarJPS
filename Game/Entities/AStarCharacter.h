#pragma once

#include "Game/Entities/Character.h"
#include "Game/Search/AStarSearch/AStarNode.h"

#if _DEBUG
#include "Game/Search/BaseSearchDebug.h"
#endif

namespace AStar
{
	class CAStarNode;
}

//this npc will use the AStart algorithm to find the best path
class CAStarCharacter final : public CCharacter
{
public:
	explicit CAStarCharacter(CGrid& rGrid);
	~CAStarCharacter() = default;

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