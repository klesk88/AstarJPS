#include "Framework/Engine/Input/InputManager.h"

#include "Framework/Engine/Input/InputMessage.h"
#include "Framework/Engine/Input/KeyboardMouse/InputHandler_KeyboardMouse.h"
#include "Framework/Utils/DebugMacros.h"

CInputManager::CInputManager()
{
    m_inputManagers.push_back(std::make_unique<CInputHandler_KeyboardMouse>());
}

CInputManager::~CInputManager()
{
}

void CInputManager::Init() const
{
	for (const std::unique_ptr<CInputHandlerBase>& rInputManager : m_inputManagers)
	{
		rInputManager->Initialize();
	}
}

void CInputManager::Shutdown()
{
    for (const std::unique_ptr<CInputHandlerBase>& rInputManager : m_inputManagers)
    {
        rInputManager->Shutdown();
    }

    m_inputManagers.clear();
}

void CInputManager::Update(const float fDeltaTime) const
{
    for (const std::unique_ptr<CInputHandlerBase>& rInputManager : m_inputManagers)
    {
        rInputManager->Update(fDeltaTime);
    }
}

void CInputManager::EndFrame() const
{
    for (const std::unique_ptr<CInputHandlerBase>& rInputManager : m_inputManagers)
    {
        rInputManager->EndFrame();
    }
}

bool CInputManager::HandleWindowsMessage(HWND /*hwnd*/, UINT umessage, WPARAM wparam, LPARAM lparam) const
{
    bool bHandled = false;
	const CInputMessage inputMessage{umessage, wparam, lparam};
    for (const std::unique_ptr<CInputHandlerBase>& rInputManager : m_inputManagers)
    {
        bHandled |= rInputManager->ProcessMessage(inputMessage);
    }

    return bHandled;
}

bool CInputManager::IsEscapePressed() const
{
    const CInputKeyboardState& KeyboardState = *GetKeyboardState();
    return KeyboardState.WasPressed(KeyboardKeyCodes::KeyCodes::KEY_ESCAPE);
}

const CInputKeyboardState* CInputManager::GetKeyboardState() const
{
    for (const std::unique_ptr<CInputHandlerBase>& rInputManager : m_inputManagers)
    {
        if (rInputManager->GetType() == InputHandleTypes::Types::KEYBOARDMOUSE)
        {
            const CInputHandler_KeyboardMouse& KeyboardMouseManager = *static_cast<const CInputHandler_KeyboardMouse*>(rInputManager.get());
            return &KeyboardMouseManager.GetKeyboardState();
        }
    }

    ASSERT(false);
    return nullptr;
}

const CInputMouseState* CInputManager::GetMouseState() const
{
    for (const std::unique_ptr<CInputHandlerBase>& rInputManager : m_inputManagers)
    {
        if (rInputManager->GetType() == InputHandleTypes::Types::KEYBOARDMOUSE)
        {
            const CInputHandler_KeyboardMouse& KeyboardMouseManager = *static_cast<const CInputHandler_KeyboardMouse*>(rInputManager.get());
            return &KeyboardMouseManager.GetMouseState();
        }
    }

    ASSERT(false);
    return nullptr;
}
