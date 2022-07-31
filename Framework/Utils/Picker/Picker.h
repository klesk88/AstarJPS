#pragma once

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

#include "Framework/Engine/Core/Event.h"
#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Utils/ClassMacros.h"
#include "Framework/Utils/Picker/PickerEvent.h"

class CInputManager;
class CMouseEvent;

class CPicker
{
	NON_COPYABLE_CLASS(CPicker)

public:
	CEventHandler<CPickerEvent> PickerEvent;

public:
	CPicker() = default;
	~CPicker() = default; 

	void Init(CInputManager& rInputManager);
	void Shutdown(CInputManager& rInputManager);
	void Update();

private:
	void OnMouseEvent(const CMouseEvent& rMouseEvent);
	void HandleMouseBtnUp(const CMouseEvent& rMouseEvent);

	void ComputeMouseStartEndPos(const CMouseEvent& rMouseEvent, DirectX::SimpleMath::Vector3& rOutStart, DirectX::SimpleMath::Vector3& rOutEnd) const;

private:
	CEventId m_mouseEventId = CEventId::GetInvalidID();
	DirectX::SimpleMath::Vector3 m_vStartPos;
	DirectX::SimpleMath::Vector3 m_vEndPos;
	bool m_bNewEvent = false;
};
