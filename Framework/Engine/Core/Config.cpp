#include "Config.h"

#include <directxmath.h>
#include <windows.h>

CConfig::CConfig()
	: m_iScreenHeight(768)
	, m_iScreenWidth(1024)
	, m_bFullScreen(false)
	, m_bEnableVSync(false)
	, m_fScreenNear(0.01f)
	, m_fScreenFar(100.f)
	, m_uGameUpdateTimeMs(1500)
	, m_fFOV(DirectX::XM_PI / 4.0f)
{}

CConfig::~CConfig()
{}

void CConfig::Load()
{
	if (IsFullScreen())
	{
		m_iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
		m_iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	}
}
