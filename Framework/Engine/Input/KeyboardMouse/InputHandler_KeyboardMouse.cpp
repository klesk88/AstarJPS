#include "Framework/Engine/Input/KeyboardMouse/InputHandler_KeyboardMouse.h"
#include "Framework/Engine/Input/InputMessage.h"

void CInputHandler_KeyboardMouse::Initialize()
{
}

void CInputHandler_KeyboardMouse::Shutdown()
{
}

void CInputHandler_KeyboardMouse::ProcessMessage(const CInputMessage& rMessage)
{
    m_keyboardState.ProcessMessage(rMessage);
    m_mouseState.ProcessMessage(rMessage);
}

void CInputHandler_KeyboardMouse::Update(const float fDeltaTime)
{
    m_keyboardState.Update(fDeltaTime);
    m_mouseState.Update(fDeltaTime);
}

void CInputHandler_KeyboardMouse::EndFrame()
{
    m_keyboardState.EndFrame();
    m_mouseState.EndFrame();
}

