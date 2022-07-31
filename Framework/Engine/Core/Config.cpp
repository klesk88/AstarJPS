#include "Framework/Engine/Core/Config.h"

#include <directxmath.h>
#include <windows.h>

void CConfig::Load()
{
	if (IsFullScreen())
	{
		m_iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		m_iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	}
}
