#pragma once

#include "../../Engine/Core/SimpleMath.h"

class CPickerEvent
{
public:
	CPickerEvent(const DirectX::SimpleMath::Vector3& vStartPos, const DirectX::SimpleMath::Vector3& vEndPos)
		: m_vStartPos(vStartPos)
		, m_vEndPos(vEndPos)
	{}

	const DirectX::SimpleMath::Vector3& GetStartPos() const { return m_vStartPos; }
	const DirectX::SimpleMath::Vector3& GetEndPos() const { return m_vEndPos; }

private:
	const DirectX::SimpleMath::Vector3 m_vStartPos;
	const DirectX::SimpleMath::Vector3 m_vEndPos;
};
