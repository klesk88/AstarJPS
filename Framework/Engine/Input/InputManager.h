#pragma once

#include "Framework/Engine/Core/Event.h"
#include "Framework/Engine/Input/InputHandlerBase.h"
#include "Framework/Engine/Input/InputHandlerTypes.h"
#include "Framework/Utils/ClassMacros.h"

//windows
#include <windows.h>

//std
#include <memory>
#include <vector>

class CConfig;
class CInputKeyboardState;
class CInputHandlerBase;
class CInputMouseState;

class CInputManager
{
	NON_COPYABLE_CLASS(CInputManager)

public:
	CInputManager();
	~CInputManager();

	void Init() const;
	void Update(const float fDeltaTime) const;
	void EndFrame() const;
	void Shutdown();
	
	[[nodiscard]] bool HandleWindowsMessage(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) const;
	
	[[nodiscard]] bool IsEscapePressed() const;
	[[nodiscard]] const CInputKeyboardState* GetKeyboardState() const;
	[[nodiscard]] const CInputMouseState* GetMouseState() const;

private:
	std::vector<std::unique_ptr<CInputHandlerBase>> m_inputManagers;
};
