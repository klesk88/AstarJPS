#pragma once

#include <d3d11.h>
#include <list>

#include "../Core/SimpleMath.h"
#include "../../Utils/ClassMacros.h"

class CDrawable3DBase;

class CDrawableManager
{
	NON_COPYABLE_CLASS(CDrawableManager)

public:
	CDrawableManager();
	~CDrawableManager();

	void Shutdown();

	void AddDrawable(CDrawable3DBase& rDrawable);
	void RemoveDrawable(CDrawable3DBase& rDrawable);

	void RenderDrawables(const DirectX::SimpleMath::Matrix& rViewMatrix, const DirectX::SimpleMath::Matrix& rWorldMatrix, const DirectX::SimpleMath::Matrix& rProjMatrix, ID3D11DeviceContext& rDeviceContext) const;

private:
	//do not use for this case weak_ptr. the entities subscribe automatically
	//when getting destroyed so no need for it. Use a double linked list so insertion
	//and removal are fast
	std::list<CDrawable3DBase*> m_drawableList;
};