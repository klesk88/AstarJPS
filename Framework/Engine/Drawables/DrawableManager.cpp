#include "Framework/Engine/Drawables/DrawableManager.h"

#include "Framework/Engine/Drawables/Drawable3DBase.h"
#include "Framework/Utils/DebugMacros.h"

using namespace DirectX::SimpleMath;

void CDrawableManager::Shutdown()
{
	for (const std::weak_ptr<CDrawable3DBase>& rDrawable3DWeakPtr : m_drawableList)
	{
        CDrawable3DBase* pDrawable = rDrawable3DWeakPtr.lock().get();

#if _DEBUG 
        //it should be always valid but in debug assert
        if (!pDrawable)
        {
            ASSERT(pDrawable != nullptr);
        }
#endif

		pDrawable->MarkAsNotInsideRenderUpdate();
	}

	m_drawableList.clear();
}

void CDrawableManager::AddDrawable(const std::weak_ptr<CDrawable3DBase>& rDrawable)
{
#if _DEBUG
    const std::shared_ptr<CDrawable3DBase> drawableSharedPtr = rDrawable.lock();
    ASSERT(drawableSharedPtr.get() != nullptr);
    
    auto searchFuncDebug = [&drawableSharedPtr](const std::weak_ptr<CDrawable3DBase>& rElement) -> bool {
        const std::shared_ptr<CDrawable3DBase> elementSharedPtr = rElement.lock();
        return drawableSharedPtr == elementSharedPtr;
    };

	std::list<std::weak_ptr<CDrawable3DBase>>::const_iterator iter = std::find_if(m_drawableList.begin(), m_drawableList.end(), searchFuncDebug);
	ASSERT(iter == m_drawableList.end());
	ASSERT(rDrawable.lock()->HasValidBuffer());
#endif

	m_drawableList.push_back(rDrawable);
}

void CDrawableManager::RemoveDrawable(const std::weak_ptr<CDrawable3DBase>& rDrawable)
{
    const std::shared_ptr<CDrawable3DBase> drawableSharedPtr = rDrawable.lock();
    auto searchFunc = [&drawableSharedPtr](const std::weak_ptr<CDrawable3DBase>& rElement) -> bool {
        const std::shared_ptr<CDrawable3DBase> elementSharedPtr = rElement.lock();
        return drawableSharedPtr == elementSharedPtr;
    };

#if _DEBUG
    std::list<std::weak_ptr<CDrawable3DBase>>::const_iterator iter = std::find_if(m_drawableList.begin(), m_drawableList.end(), searchFunc);
    ASSERT(iter != m_drawableList.end());
#endif

	m_drawableList.remove_if(searchFunc);
}

void CDrawableManager::RenderDrawables(const Matrix& rViewMatrix, const Matrix& rWorldMatrix, const Matrix& rProjMatrix, ID3D11DeviceContext& rDeviceContext) const
{
	for (const std::weak_ptr<CDrawable3DBase>& rDrawable3DWeakPtr : m_drawableList)
	{
		CDrawable3DBase* pDrawable = rDrawable3DWeakPtr.lock().get();

#if _DEBUG 
		//it should be always valid but in debug assert
		if (!pDrawable)
        {
            ASSERT(pDrawable != nullptr);
		}
#endif

		pDrawable->Render(rViewMatrix, rWorldMatrix, rProjMatrix, rDeviceContext);
	}
}
