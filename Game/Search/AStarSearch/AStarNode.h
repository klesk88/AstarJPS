#pragma once

#include "../BaseNode.h"

namespace AStar
{
	class CAStarNode final : public Search::CBaseNode
	{
	public:
		CAStarNode(const int iIndex);
	};
}