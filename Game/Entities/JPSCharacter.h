#pragma once

//this character will use the jump point search (JPS) algorithm
//to find the best path

#include "Character.h"
#include "../Search/JumpPointSearch/JPSData.h"

#if _DEBUG
#include "../Search/BaseSearchDebug.h"
#endif

namespace JPS
{
	class CJPSNode;
}

class CJPSCharacter final : public CCharacter
{
public:
	CJPSCharacter(CGrid& rGrid);

	void Init(const int iStartCell, const int iTargetPos) override;
	void Clear() override;

private:
	void PerformSearch(const int iTargetLocation) override;

#if _DEBUG
public:
	void UpdateImgui() override;

private:
	CBaseSearchDebug<JPS::CJPSNode> m_searchDebug;
#endif
};