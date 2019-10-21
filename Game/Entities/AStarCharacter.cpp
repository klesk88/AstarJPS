#include "AStarCharacter.h"

#include <DirectXColors.h>

#include "../Search/AStarSearch/AStarSearch.h"
#include "../../Framework/Utils/DebugMacros.h"

CAStarCharacter::CAStarCharacter(CGrid& rGrid)
	: CCharacter(rGrid, CGrid::eCollisionType::CHARACTER, DirectX::Colors::Brown)
	DEBUG_ONLY(, m_searchDebug("AStar", DirectX::Colors::Purple))
{}

void CAStarCharacter::Init(const int iStartCell, const int iTargetPos)
{
#if _DEBUG
	m_searchDebug.Clear();
#endif

	CCharacter::Init(iStartCell, iTargetPos);
}

void CAStarCharacter::PerformSearch(const int iTargetLocation)
{
	AStar::CAStarInput aStartInput(m_rGrid, m_iCurrentPos, iTargetLocation, m_path DEBUG_ONLY(, m_searchDebug));
	aStartInput.Search();
}

void CAStarCharacter::Clear()
{
	CCharacter::Clear();

#if _DEBUG
	m_searchDebug.Clear();
#endif
}

#if _DEBUG
void CAStarCharacter::UpdateImgui()
{
	CCharacter::UpdateImgui();
	m_searchDebug.RenderImgui(m_rGrid);
}
#endif