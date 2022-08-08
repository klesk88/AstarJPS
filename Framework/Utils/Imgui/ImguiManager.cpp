#include "ImguiManager.h"

#include "Framework/Utils/Imgui/imgui.h"
#include "Framework/Utils/Imgui/imgui_impl_dx11.h"
#include "Framework/Utils/Imgui/imgui_impl_win32.h"

void CImguiManager::InitImgui(HWND hwnd, ID3D11Device& rDevice, ID3D11DeviceContext& rDeviceContext)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(&rDevice, &rDeviceContext);
	ImGui::StyleColorsDark();
}

void CImguiManager::Update()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImguiUpdate.Emit();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

