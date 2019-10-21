#pragma once

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>
#include <windows.h>

#include "../Drawables/DrawableManager.h"
#include "../Core/SimpleMath.h"
#include "../../Utils/ClassMacros.h"
#include "../../Utils/Imgui/ImguiManager.h"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

class CConfig;
class CDrawable3DBase;

class CRenderer
{
	NON_COPYABLE_CLASS(CRenderer)

public:
	CRenderer();
	~CRenderer();

	bool Initialize(const CConfig& rConfig, HWND hwnd);
	void Shutdown();

	void PreUpdate();
	void Update(const DirectX::SimpleMath::Matrix& rViewMatrix, const DirectX::SimpleMath::Matrix& rProjMatrix);
	void PostUpdate(const bool bVSyncEnable);

	void AddDrawable(CDrawable3DBase& rDrawable) { m_drawableManger.AddDrawable(rDrawable); }
	void RemoveDrawable(CDrawable3DBase& rDrawable) { m_drawableManger.RemoveDrawable(rDrawable); }

	CEventHandler<>& GetImguiEventHandler() { return m_imguiManager.ImguiUpdate; }
	ID3D11Device& GetDevice() { return *m_pDevice; }
	ID3D11DeviceContext& GetDeviceContext() { return *m_pDeviceContext; }

private:
	bool InitBlendState();
	bool InitRasterState();
	bool InitDepthStancilState();
	bool InitDepthStencil();
	bool InitDepthBuffer(const CConfig& rConfig);
	bool InitSwapChain(const CConfig& rConfig, const unsigned int uNumerator, const unsigned int uDenominator, HWND hwnd);
	bool InitBackBufferPtr();
	bool InitAdapterAndFactory(const CConfig& rConfig, unsigned int& ruOutNumerator, unsigned int& ruOutDenominator);
	void InitDeviceContext(const CConfig& rConfig);

private:
	CDrawableManager m_drawableManger;
	CImguiManager m_imguiManager;

	char m_videoCardDescription[128];
	DirectX::SimpleMath::Matrix m_worldMatrix;
	int m_iVideoCardMemory;
	IDXGISwapChain* m_pSwapChain;
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	ID3D11RenderTargetView* m_pRenderTargetView;
	ID3D11Texture2D* m_pDepthStencilBuffer;
	ID3D11DepthStencilState* m_pDepthStencilState;
	ID3D11DepthStencilView* m_pDepthStencilView;
	ID3D11RasterizerState* m_pRasterState;
	ID3D11BlendState* m_pBlendState;
};
