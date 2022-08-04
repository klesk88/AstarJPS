#include "Framework/Engine/Core/Config.h"

#include <directxmath.h>
#include <windows.h>

void CConfig::Load()
{
	//TODO: we should read am actual config file here (a json probably) at some point

	if (IsFullScreen())
	{
		m_iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		m_iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	}
}
