#pragma once

#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Engine/Drawables/DrawableManager.h"
#include "Framework/Utils/ClassMacros.h"
#include "Framework/Utils/Imgui/ImguiManager.h"

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

//directx
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3d11.h>

//windows
#include <windows.h>

class CDrawable3DBase;
class CWindowConfig;

class CRenderer
{
	NON_COPYABLE_CLASS(CRenderer)

public:
	CRenderer() = default;
	~CRenderer() = default;

	[[nodiscard]] bool Initialize(const CWindowConfig& rWindowConfig, HWND hwnd);
	void Shutdown();

	void PreUpdate();
	void Update(const DirectX::SimpleMath::Matrix& rViewMatrix, const DirectX::SimpleMath::Matrix& rProjMatrix);
	void PostUpdate(const bool bVSyncEnable);

	void AddDrawable(CDrawable3DBase& rDrawable) { m_drawableManger.AddDrawable(rDrawable); }
	void RemoveDrawable(CDrawable3DBase& rDrawable) { m_drawableManger.RemoveDrawable(rDrawable); }

	[[nodiscard]] CEventHandler<>& GetImguiEventHandler();
	[[nodiscard]] ID3D11Device& GetDevice();
	[[nodiscard]] ID3D11DeviceContext& GetDeviceContext();

private:
	[[nodiscard]] bool InitBlendState();
	[[nodiscard]] bool InitRasterState();
	[[nodiscard]] bool InitDepthStancilState();
	[[nodiscard]] bool InitDepthStencil();
	[[nodiscard]] bool InitDepthBuffer(const CWindowConfig& rWindowConfig);
	[[nodiscard]] bool InitSwapChain(const CWindowConfig& rWindowConfig, const unsigned int uNumerator, const unsigned int uDenominator, HWND hwnd);
	[[nodiscard]] bool InitBackBufferPtr();
	[[nodiscard]] bool InitAdapterAndFactory(const CWindowConfig& rWindowConfig, unsigned int& ruOutNumerator, unsigned int& ruOutDenominator);
	void InitDeviceContext(const CWindowConfig& rWindowConfig);

private:
	CDrawableManager m_drawableManger;
	CImguiManager m_imguiManager;

	char m_videoCardDescription[128];
	DirectX::SimpleMath::Matrix m_worldMatrix = DirectX::XMMatrixIdentity();
	int m_iVideoCardMemory = 0;
	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11Device* m_pDevice = nullptr;
	ID3D11DeviceContext* m_pDeviceContext = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
	ID3D11Texture2D* m_pDepthStencilBuffer = nullptr;
	ID3D11DepthStencilState* m_pDepthStencilState = nullptr;
	ID3D11DepthStencilView* m_pDepthStencilView = nullptr;
	ID3D11RasterizerState* m_pRasterState = nullptr;
	ID3D11BlendState* m_pBlendState = nullptr;
};

inline CEventHandler<>& CRenderer::GetImguiEventHandler() { return m_imguiManager.ImguiUpdate; }
inline ID3D11Device& CRenderer::GetDevice() { return *m_pDevice; }
inline ID3D11DeviceContext& CRenderer::GetDeviceContext() { return *m_pDeviceContext; }