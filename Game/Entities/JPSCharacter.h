#pragma once

#include "Game/Entities/Character.h"
#include "Game/Search/JumpPointSearch/JPSData.h"

#if _DEBUG
#include "Game/Search/BaseSearchDebug.h"
#endif

namespace JPS
{
	class CJPSNode;
}

//this character will use the jump point search (JPS) algorithm
//to find the best path
class CJPSCharacter final : public CCharacter
{
public:
	explicit CJPSCharacter(CGrid& rGrid);
	~CJPSCharacter() = default;

	//CCharacter
	void Init(const int iStartCell, const int iTargetPos) override;
	void Clear() override;
	//CCharacter

private:
	//CCharacter
	void PerformSearch(const int iTargetLocation) override;
	//CCharacter

#if _DEBUG
public:
	void UpdateImgui() override;

private:
	CBaseSearchDebug<JPS::CJPSNode> m_searchDebug;
#endif
};