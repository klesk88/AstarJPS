#pragma once

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

#include "Framework/Engine/Core/Event.h"
#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Utils/ClassMacros.h"
#include "Framework/Utils/Picker/PickerEvent.h"

class CInputMouseState;
class CManagerUpdateInput;

class CPicker
{
	NON_COPYABLE_CLASS(CPicker)

public:
	CEventHandler<CPickerEvent> PickerEvent;

public:
	CPicker() = default;
	~CPicker() = default; 

	void Init();
	void Shutdown();
	void Update(const CManagerUpdateInput& rInput);

private:
	void ComputeMouseStartEndPos(const CInputMouseState& rMouseState, DirectX::SimpleMath::Vector3& rOutStart, DirectX::SimpleMath::Vector3& rOutEnd) const;
};
