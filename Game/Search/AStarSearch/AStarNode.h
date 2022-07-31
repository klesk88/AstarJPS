#pragma once

#include "Game/Search/BaseNode.h"

namespace AStar
{
	class CAStarNode final : public Search::CBaseNode
	{
	public:
		explicit CAStarNode(const int iIndex);
		~CAStarNode() = default;
	};
}