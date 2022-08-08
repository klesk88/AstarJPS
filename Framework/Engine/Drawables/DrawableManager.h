#pragma once

#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Utils/ClassMacros.h"

//directx
#include <d3d11.h>

//std
#include <list>
#include <memory>

class CDrawable3DBase;

class CDrawableManager
{
	NON_COPYABLE_CLASS(CDrawableManager)

public:
	CDrawableManager() = default;
	~CDrawableManager() = default;

	void Shutdown();

	void AddDrawable(const std::weak_ptr<CDrawable3DBase>& rDrawable);
	void RemoveDrawable(const std::weak_ptr<CDrawable3DBase>& rDrawable);

	void RenderDrawables(const DirectX::SimpleMath::Matrix& rViewMatrix, const DirectX::SimpleMath::Matrix& rWorldMatrix, const DirectX::SimpleMath::Matrix& rProjMatrix, ID3D11DeviceContext& rDeviceContext) const;

private:
	//The entities unsubscribe automatically when getting destroyed. Use a double linked list so insertion and removal are fast.
	//Store weak ptr just as a safety measure. In this case the performance impact of using a weak_ptr is not an issue
	std::list<std::weak_ptr<CDrawable3DBase>> m_drawableList;
};