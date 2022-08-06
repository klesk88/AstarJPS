#include "Framework/Engine/Core/WindowConfig.h"

//windows
#include <windows.h>

void CWindowConfig::Load()
{
	if (IsFullScreen())
	{
		m_iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		m_iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	}
}
