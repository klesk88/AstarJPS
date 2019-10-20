#include "JPSCharacter.h"

#include <DirectXColors.h>

#include "../Search/JumpPointSearch/JPSSearch.h"
#include "../../Framework/Utils/DebugMacros.h"

CJPSCharacter::CJPSCharacter(CGrid& rGrid)
	: CCharacter(rGrid, CGrid::eCollisionType::CHARACTER, DirectX::Colors::White)
	DEBUG_ONLY(, m_searchDebug("JPS", DirectX::Colors::Brown))
{}

void CJPSCharacter::Init(const int iStartCell, const int iTargetPos)
{
#if _DEBUG
	m_searchDebug.Clear();
#endif

	CCharacter::Init(iStartCell, iTargetPos);
}

void CJPSCharacter::OnDisable()
{
	Clear();
}

void CJPSCharacter::PerformSearch(const int iTargetLocation)
{
	JPS::CJPSInput aJPSInput(m_rGrid, m_iCurrentPos, iTargetLocation, m_path DEBUG_ONLY(, m_searchDebug));
	aJPSInput.Search();
}

void CJPSCharacter::Clear()
{
	CCharacter::Clear();

#if _DEBUG
	m_searchDebug.Clear();
#endif
}

#if _DEBUG
void CJPSCharacter::UpdateImgui()
{
	CCharacter::UpdateImgui();
	m_searchDebug.RenderImgui(m_rGrid);
}
#endif
