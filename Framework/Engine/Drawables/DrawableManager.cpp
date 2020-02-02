#include "DrawableManager.h"

#include "Drawable3DBase.h"
#include "../../Utils/DebugMacros.h"

using namespace DirectX::SimpleMath;

CDrawableManager::CDrawableManager()
{}

CDrawableManager::~CDrawableManager()
{}

void CDrawableManager::Shutdown()
{
	for (CDrawable3DBase* pDrawable3D : m_drawableList)
	{
		pDrawable3D->MarkAsNotInsideRenderUpdate();
	}

	m_drawableList.clear();
}

void CDrawableManager::AddDrawable(CDrawable3DBase& rDrawable)
{
#if _DEBUG
	std::list<CDrawable3DBase*>::const_iterator iter = std::find(m_drawableList.begin(), m_drawableList.end(), &rDrawable);
	ASSERT(iter == m_drawableList.end());
	ASSERT(rDrawable.HasValidBuffer());
#endif

	m_drawableList.push_back(&rDrawable);
}

void CDrawableManager::RemoveDrawable(CDrawable3DBase& rDrawable)
{
	m_drawableList.remove(&rDrawable);
}

void CDrawableManager::RenderDrawables(const Matrix& rViewMatrix, const Matrix& rWorldMatrix, const Matrix& rProjMatrix, ID3D11DeviceContext& rDeviceContext) const
{
	for (CDrawable3DBase* pDrawable3D : m_drawableList)
	{
		pDrawable3D->Render(rViewMatrix, rWorldMatrix, rProjMatrix, rDeviceContext);
	}
}
