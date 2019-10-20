#include "Window.h"

#include "Config.h"
#include "../Engine.h"

#include "../../Utils/Imgui/imgui.h"
#include "../../Utils/Imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace SystemHelpers
{
	LRESULT CALLBACK MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hwnd, umessage, wparam, lparam))
		{
			return 0;
		}

		if (CEngine::GetInstance()->GetInputManager().HandleWindowsMessage(hwnd, umessage, wparam, lparam))
		{
			return 0;
		}

		switch (umessage)
		{
			// Check if the window is being destroyed.
			case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
			// Check if the window is being closed.
			case WM_CLOSE:
			{
				PostQuitMessage(0);
				return 0;
			}
			// All other messages pass to the message handler in the system class.
			default:
			{
				return MessageHandler(hwnd, umessage, wparam, lparam);
			}
		}
	}
}

CWindow::CWindow()
	: m_applicationName("Demo")
	, m_hInstance(nullptr)
	, m_hwnd(nullptr)
{}

CWindow::~CWindow()
{}

void CWindow::Init(CConfig& rConfig)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	m_hInstance = GetModuleHandle(nullptr);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = SystemHelpers::WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	if (rConfig.IsFullScreen())
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)rConfig.GetScreenWidth();
		dmScreenSettings.dmPelsHeight = (unsigned long)rConfig.GetScreenHeight();
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		posX = posY = 0;
	}
	else
	{
		posX = static_cast<int>((GetSystemMetrics(SM_CXSCREEN) - rConfig.GetScreenWidth()) * 0.5f);
		posY = static_cast<int>((GetSystemMetrics(SM_CYSCREEN) - rConfig.GetScreenHeight()) * 0.5f);
	}

	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, rConfig.GetScreenWidth(), rConfig.GetScreenHeight(), nullptr, nullptr, m_hInstance, nullptr);

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
}