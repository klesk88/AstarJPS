#include "Framework/Engine/Render/Renderer.h"

#include "Framework/Engine/Core/WindowConfig.h"
#include "Framework/Utils/DebugMacros.h"

//directx
#include <DirectXColors.h>

using namespace DirectX::SimpleMath;

bool CRenderer::Initialize(const CWindowConfig& rWindowConfig, HWND hwnd)
{
	unsigned int uNumerator = 0;
	unsigned int uDenominator = 0;

	if(!InitAdapterAndFactory(rWindowConfig, uNumerator, uDenominator))
	{
		return false;
	}

	if (!InitSwapChain(rWindowConfig, uNumerator, uDenominator, hwnd))
	{
		return false;
	}

	if (!InitBackBufferPtr())
	{
		return false;
	}

	if (!InitDepthBuffer(rWindowConfig))
	{
		return false;
	}

	if (!InitDepthStencil())
	{
		return false;
	}

	if (!InitDepthStancilState())
	{
		return false;
	}

	if (!InitRasterState())
	{
		return false;
	}

	if (!InitBlendState())
	{
		return false;
	}

	InitDeviceContext(rWindowConfig);
	m_imguiManager.InitImgui(hwnd, *m_pDevice, *m_pDeviceContext);

	return true;
}

void CRenderer::Shutdown()
{
	m_drawableManger.Shutdown();

	// Before shutting down set to windowed mode or when you release the swap chain it will throw an exception.
	if (m_pSwapChain)
	{
		m_pSwapChain->SetFullscreenState(false, nullptr);
	}

	if (m_pRasterState)
	{
		m_pRasterState->Release();
		m_pRasterState = nullptr;
	}

	if (m_pBlendState)
	{
		m_pBlendState->Release();
		m_pBlendState = nullptr;
	}

	if (m_pDepthStencilView)
	{
		m_pDepthStencilView->Release();
		m_pDepthStencilView = nullptr;
	}

	if (m_pDepthStencilState)
	{
		m_pDepthStencilState->Release();
		m_pDepthStencilState = nullptr;
	}

	if (m_pDepthStencilBuffer)
	{
		m_pDepthStencilBuffer->Release();
		m_pDepthStencilBuffer = nullptr;
	}

	if (m_pRenderTargetView)
	{
		m_pRenderTargetView->Release();
		m_pRenderTargetView = nullptr;
	}

	if (m_pDeviceContext)
	{
		m_pDeviceContext->Release();
		m_pDeviceContext = nullptr;
	}

	if (m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	if (m_pSwapChain)
	{
		m_pSwapChain->Release();
		m_pSwapChain = nullptr;
	}
}

bool CRenderer::InitBlendState()
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	const HRESULT result = m_pDevice->CreateBlendState(&blendDesc, &m_pBlendState);

	return SUCCEEDED(result);
}

bool CRenderer::InitRasterState()
{
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(rasterDesc));

	// Setup the raster description which will determine how and what polygons will be drawn.
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	const HRESULT result = m_pDevice->CreateRasterizerState(&rasterDesc, &m_pRasterState);
	return SUCCEEDED(result);
}

bool CRenderer::InitDepthStancilState()
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	const HRESULT result = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &depthStencilViewDesc, &m_pDepthStencilView);
	return SUCCEEDED(result);
}

bool CRenderer::InitDepthStencil()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	const HRESULT result = m_pDevice->CreateDepthStencilState(&depthStencilDesc, &m_pDepthStencilState);
	return SUCCEEDED(result);
}

bool CRenderer::InitDepthBuffer(const CWindowConfig& rWindowConfig)
{
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = rWindowConfig.GetScreenWidth();
	depthBufferDesc.Height = rWindowConfig.GetScreenHeight();
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	const HRESULT result = m_pDevice->CreateTexture2D(&depthBufferDesc, nullptr, &m_pDepthStencilBuffer);
	return SUCCEEDED(result);
}

bool CRenderer::InitSwapChain(const CWindowConfig& rWindowConfig, const unsigned int uNumerator, const unsigned int uDenominator, HWND hwnd)
{
	HRESULT result;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;

	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
	swapChainDesc.BufferCount = 1;

	// Set the width and height of the back buffer.
	swapChainDesc.BufferDesc.Width = rWindowConfig.GetScreenWidth();
	swapChainDesc.BufferDesc.Height = rWindowConfig.GetScreenHeight();

	// Set regular 32-bit surface for the back buffer.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.
	if (rWindowConfig.GetVSyncEnable())
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = uNumerator;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = uDenominator;
	}
	else
	{
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	}

	// Set the usage of the back buffer.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	swapChainDesc.OutputWindow = hwnd;

	// Turn multisampling off.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	// Set to full screen or windowed mode.
	if (rWindowConfig.IsFullScreen())
	{
		swapChainDesc.Windowed = false;
	}
	else
	{
		swapChainDesc.Windowed = true;
	}

	// Set the scan line ordering and scaling to unspecified.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	swapChainDesc.Flags = 0;

	// Set the feature level to DirectX 11.
	featureLevel = D3D_FEATURE_LEVEL_11_0;

	// Create the swap chain, Direct3D device, and Direct3D device context.
	result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1,
		D3D11_SDK_VERSION, &swapChainDesc, &m_pSwapChain, &m_pDevice, nullptr, &m_pDeviceContext);
	
	return SUCCEEDED(result);
}

bool CRenderer::InitBackBufferPtr()
{
	ID3D11Texture2D* pBackBufferPtr = nullptr;
	// Get the pointer to the back buffer.
	HRESULT result = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBufferPtr);
	if (FAILED(result))
	{
		return false;
	}

	// Create the render target view with the back buffer pointer.
	result = m_pDevice->CreateRenderTargetView(pBackBufferPtr, nullptr, &m_pRenderTargetView);
	if (FAILED(result))
	{
		return false;
	}

	// Release pointer to the back buffer as we no longer need it.
	pBackBufferPtr->Release();
	pBackBufferPtr = 0;

	return true;
}

bool CRenderer::InitAdapterAndFactory(const CWindowConfig& rWindowConfig, unsigned int& ruOutNumerator, unsigned int& ruOutDenominator)
{
	HRESULT result;
	IDXGIFactory* pFactory;
	IDXGIAdapter* pAdapter;
	IDXGIOutput* pAdapterOutput;
	unsigned int uNumModes = 0;
	size_t stringLength;
	DXGI_MODE_DESC* pDisplayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int iError = 0;
	ruOutDenominator = 0;
	ruOutNumerator = 0;

	// Create a DirectX graphics interface factory.
	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);
	if (FAILED(result))
	{
		return false;
	}

	// Use the factory to create an adapter for the primary graphics interface (video card).
	result = pFactory->EnumAdapters(0, &pAdapter);
	if (FAILED(result))
	{
		return false;
	}

	// Enumerate the primary adapter output (monitor).
	result = pAdapter->EnumOutputs(0, &pAdapterOutput);
	if (FAILED(result))
	{
		return false;
	}

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	result = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &uNumModes, nullptr);
	if (FAILED(result))
	{
		return false;
	}

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	pDisplayModeList = new DXGI_MODE_DESC[uNumModes];
	if (!pDisplayModeList)
	{
		return false;
	}

	// Now fill the display mode list structures.
	result = pAdapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &uNumModes, pDisplayModeList);
	if (FAILED(result))
	{
		return false;
	}

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	for (unsigned i = 0; i < uNumModes; i++)
	{
		if (pDisplayModeList[i].Width == (unsigned int)rWindowConfig.GetScreenWidth())
		{
			if (pDisplayModeList[i].Height == (unsigned int)rWindowConfig.GetScreenHeight())
			{
				ruOutNumerator = pDisplayModeList[i].RefreshRate.Numerator;
				ruOutDenominator = pDisplayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	// Get the adapter (video card) description.
	result = pAdapter->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		return false;
	}

	// Store the dedicated video card memory in megabytes.
	m_iVideoCardMemory = static_cast<int>(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Convert the name of the video card to a character array and store it.
	iError = wcstombs_s(&stringLength, m_videoCardDescription, 128, adapterDesc.Description, 128);
	if (iError != 0)
	{
		return false;
	}

	// Release the display mode list.
	delete[] pDisplayModeList;
	pDisplayModeList = 0;

	// Release the adapter output.
	pAdapterOutput->Release();
	pAdapterOutput = 0;

	// Release the adapter.
	pAdapter->Release();
	pAdapter = 0;

	// Release the factory.
	pFactory->Release();
	pFactory = 0;
	return true;
}

void CRenderer::InitDeviceContext(const CWindowConfig& rWindowConfig)
{
	// Set the depth stencil state.
	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 1);
	// Bind the render target view and depth stencil buffer to the output render pipeline.
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	UINT sampleMask = 0xffffffff;
	//bind the blend state
	m_pDeviceContext->OMSetBlendState(m_pBlendState, blendFactor, sampleMask);

	// Now set the rasterizer state.
	m_pDeviceContext->RSSetState(m_pRasterState);
	D3D11_VIEWPORT viewport = CD3D11_VIEWPORT(
		0.f,
		0.f,
		static_cast<float>(rWindowConfig.GetScreenWidth()),
		static_cast<float>(rWindowConfig.GetScreenHeight()));

	// Create the viewport.
	m_pDeviceContext->RSSetViewports(1, &viewport);
}

void CRenderer::PreUpdate()
{
	ID3D11RenderTargetView* const targets[1] = { m_pRenderTargetView };
	m_pDeviceContext->OMSetRenderTargets(1, targets, m_pDepthStencilView);

	// Clear the back buffer.
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, DirectX::Colors::CornflowerBlue);

	// Clear the depth buffer.
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void CRenderer::Update(const Matrix& rViewMatrix, const Matrix& rProjMatrix)
{
	m_drawableManger.RenderDrawables(rViewMatrix, m_worldMatrix, rProjMatrix, *m_pDeviceContext);
	m_imguiManager.Update();
}

void CRenderer::PostUpdate(const bool bVSyncEnable)
{
	// Present the back buffer to the screen since rendering is complete.
	if (bVSyncEnable)
	{
		// Lock to screen refresh rate.
		m_pSwapChain->Present(1, 0);
	}
	else
	{
		// Present as fast as possible.
		m_pSwapChain->Present(0, 0);
	}

	return;
}
