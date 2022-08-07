#pragma once

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

#include "../../Engine/Core/SimpleMath.h"

class CPickerEvent
{
public:
	explicit CPickerEvent(const DirectX::SimpleMath::Vector3& vStartPos, const DirectX::SimpleMath::Vector3& vEndPos);
	~CPickerEvent() = default;

	[[nodiscard]] const DirectX::SimpleMath::Vector3& GetStartPos() const { return m_vStartPos; }
	[[nodiscard]] const DirectX::SimpleMath::Vector3& GetEndPos() const { return m_vEndPos; }

private:
	const DirectX::SimpleMath::Vector3 m_vStartPos;
	const DirectX::SimpleMath::Vector3 m_vEndPos;
};

inline CPickerEvent::CPickerEvent(const DirectX::SimpleMath::Vector3& vStartPos, const DirectX::SimpleMath::Vector3& vEndPos)
    : m_vStartPos(vStartPos)
    , m_vEndPos(vEndPos)
{}