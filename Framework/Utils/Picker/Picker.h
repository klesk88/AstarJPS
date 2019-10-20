#pragma once

#include "PickerEvent.h"
#include "../../Engine/Core/Event.h"
#include "../../Engine/Core/SimpleMath.h"

class CInputManager;
class CMouseEvent;

class CPicker
{
public:
	CEventHandler<CPickerEvent> PickerEvent;

public:
	CPicker() = default;

	void Init(CInputManager& rInputManager);
	void Update();

private:
	void OnMouseEvent(const CMouseEvent& rMouseEvent);
	void HandleMouseBtnUp(const CMouseEvent& rMouseEvent);

	void ComputeMouseStartEndPos(const CMouseEvent& rMouseEvent, DirectX::SimpleMath::Vector3& rOutStart, DirectX::SimpleMath::Vector3& rOutEnd) const;

private:
	CEventId m_mouseEventId;
	DirectX::SimpleMath::Vector3 m_vStartPos;
	DirectX::SimpleMath::Vector3 m_vEndPos;
	bool m_bNewEvent : 1;
};
