#pragma once



#include "../DebugMacros.h"

#include <d3d11.h>

#include "../ClassMacros.h"
#include "../../Engine/Core/Event.h"

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

