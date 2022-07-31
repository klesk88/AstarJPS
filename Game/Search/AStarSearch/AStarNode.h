#pragma once

#include "Game/Search/BaseNode.h"

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

namespace AStar
{
	class CAStarNode final : public Search::CBaseNode
	{
	public:
		explicit CAStarNode(const int iIndex);
		~CAStarNode() = default;
	};
}