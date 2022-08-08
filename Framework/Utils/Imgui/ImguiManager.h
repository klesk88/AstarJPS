#pragma once

//framework
#include "Framework/Engine/Core/Event.h"
#include "Framework/Utils/ClassMacros.h"
#include "Framework/Utils/DebugMacros.h"

//directx
#include <d3d11.h>

class CImguiManager
{
	NON_COPYABLE_CLASS(CImguiManager)

public:
	CEventHandler<> ImguiUpdate;

public:
	CImguiManager() = default;

	void InitImgui(HWND hwnd, ID3D11Device& rDevice, ID3D11DeviceContext& rDeviceContext);
	void Update();

	CEventHandler<>& GetUpdateEventHandler() { return ImguiUpdate; }
};

