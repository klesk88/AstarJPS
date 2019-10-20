#include "DrawableManager.h"

#include "Drawable3DBase.h"
#include "../../Utils/DebugMacros.h"

using namespace DirectX::SimpleMath;

CDrawableManager::CDrawableManager()
{}

CDrawableManager::~CDrawableManager()
{}

void CDrawableManager::AddDrawable(const CDrawable3DBase& rDrawable)
{
#if _DEBUG
	std::list<const CDrawable3DBase*>::const_iterator iter = std::find(m_drawableList.begin(), m_drawableList.end(), &rDrawable);
	ASSERT(iter == m_drawableList.end());
#endif

	m_drawableList.push_back(&rDrawable);
}

void CDrawableManager::RemoveDrawable(const CDrawable3DBase& rDrawable)
{
	m_drawableList.remove(&rDrawable);
}

void CDrawableManager::RenderDrawables(const Matrix& rViewMatrix, const Matrix& rWorldMatrix, const Matrix& rProjMatrix, ID3D11DeviceContext& rDeviceContext) const
{
	for (const CDrawable3DBase* pDrawable3D : m_drawableList)
	{
		pDrawable3D->Render(rViewMatrix, rWorldMatrix, rProjMatrix, rDeviceContext);
	}
}
