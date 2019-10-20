#include "Entity.h"

#include "../GameManager.h"
#include "../Engine.h"

CEntity::CEntity()
	: m_iCellPosIndex(0)
	, m_bIsEnable(false)
{}

CEntity::~CEntity()
{
	SetEnable(false);
}

void CEntity::SetEnable(const bool bEnable)
{
	if (bEnable)
	{
		OnEnable();
		CEngine::GetInstance()->GetGameManager().AddEntityToUpdate(*this);
	}
	else
	{
		OnDisable();
		CEngine::GetInstance()->GetGameManager().RemoveEntityFromUpdate(*this);
	}

	m_bIsEnable = bEnable;
}
