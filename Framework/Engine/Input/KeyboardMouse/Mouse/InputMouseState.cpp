#include "Framework/Engine/Input/KeyboardMouse/Mouse/InputMouseState.h"

#include "Framework/Engine/Input/InputCommonIncludes.h"
#include "Framework/Engine/Input/InputMessage.h"
#include "Framework/Utils/Imgui/imgui.h"

CInputMouseState::CInputMouseState()
    : CInputStateBase(static_cast<unsigned int>(MouseKeyCodes::KeyCodes::KEY_COUNT))
{
    //https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawmouse
    HWND activeWindow = GetActiveWindow();

    // Mouse
    RAWINPUTDEVICE inputDevices[2];
    inputDevices[0].usUsagePage = 0x01;
    inputDevices[0].usUsage = 0x02;
    inputDevices[0].dwFlags = 0;
    inputDevices[0].hwndTarget = activeWindow;

    if (!RegisterRawInputDevices(inputDevices, 1, sizeof(RAWINPUTDEVICE)))
    {
        ASSERT(false);
    }
}

void CInputMouseState::ProcessMessage(const CInputMessage& rMessage)
{
    if (ImGui::GetCurrentContext() && ImGui::GetIO().WantCaptureMouse)
    {
        return;
    }

    switch (rMessage.GetMessage())
    {
    case WM_MOUSEMOVE:
    {
        m_iPosX = LOWORD(rMessage.GetLParam());
        m_iPosY = HIWORD(rMessage.GetLParam());
        break;
    }
    case WM_INPUT:
    {
        HandleRawInput(rMessage);
        break;
    }
    case WM_MOUSELEAVE:
    {
        m_bHasFocus = false;
        break;
    }
    case WM_RBUTTONDOWN:
    {
        m_buttonsList[static_cast<int>(MouseKeyCodes::KeyCodes::RIGHT_BUTTON)].SetIsPressed();
        break;
    }
    case WM_RBUTTONUP:
    {
        m_buttonsList[static_cast<int>(MouseKeyCodes::KeyCodes::RIGHT_BUTTON)].ClearIsPressed();
        break;
    }
    case WM_LBUTTONDOWN:
    {
        m_buttonsList[static_cast<int>(MouseKeyCodes::KeyCodes::LEFT_BUTTON)].SetIsPressed();
        break;
    }
    case WM_LBUTTONUP:
    {
        m_buttonsList[static_cast<int>(MouseKeyCodes::KeyCodes::LEFT_BUTTON)].ClearIsPressed();
        break;
    }
    case WM_MOUSEWHEEL:
    {
        m_fMouseWheelDelta = GET_WHEEL_DELTA_WPARAM(rMessage.GetWParam());
        break;
    }
    default:
        break;
    }
}

void CInputMouseState::EndFrame()
{
    m_fPosDeltaXThisFrame = 0.f;
    m_fPosDeltaYThisFrame = 0.f;
    m_fMouseWheelDelta = 0.f;
}

void CInputMouseState::HandleRawInput(const CInputMessage& rMessage)
{
    //https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawmouse

    RAWINPUT* pRawInput = nullptr;
    UINT uBufferSize = 0;
    GetRawInputData((HRAWINPUT)rMessage.GetLParam(), RID_INPUT, nullptr, &uBufferSize, sizeof(RAWINPUTHEADER));

    pRawInput = (PRAWINPUT)malloc(uBufferSize);
    if (!pRawInput)
    {
        ASSERT(false);
        return;
    }

    // Get raw input data buffer size
    if (!GetRawInputData((HRAWINPUT)rMessage.GetLParam(), RID_INPUT, pRawInput, &uBufferSize, sizeof(RAWINPUTHEADER)))
    {
        ASSERT(false);
        return;
    }

    if (pRawInput->header.dwType == RIM_TYPEMOUSE)
    {
        RAWMOUSE const& rawMouse = pRawInput->data.mouse;

        // Mouse Movement
        m_fPosDeltaXThisFrame += (float)rawMouse.lLastX;
        m_fPosDeltaYThisFrame += (float)rawMouse.lLastY;
    }
}
