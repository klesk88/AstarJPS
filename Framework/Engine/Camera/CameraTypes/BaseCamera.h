#pragma once

#include "Framework/Engine/Core/Event.h"
#include "Framework/Engine/Core/SimpleMath.h"
#include "Framework/Utils/ClassMacros.h"

//directx
#include <directxmath.h>

//std
#include <vector>

class CConfig;
class CInputManager;
class CKeyboardEvent;
class CMouseEvent;

class CBaseCamera
{
	NON_COPYABLE_CLASS(CBaseCamera)

protected:
	enum class eDir : char
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT,
		FORWARD,
		BACKWARDS,

		COUNT
	};

protected:
    //constructor can be accesses only by the children
    explicit CBaseCamera(const CConfig& rConfig, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& defaultUp, const DirectX::SimpleMath::Vector3& defaultFwd, const DirectX::SimpleMath::Vector3& defaultRight, CInputManager& rInputManager);

public:
	virtual ~CBaseCamera();

	virtual void Update() = 0;

	void Shutdown(CInputManager& rInputManager);

	[[nodiscard]] const DirectX::SimpleMath::Matrix& GetViewMatrix() const;
	[[nodiscard]] const DirectX::SimpleMath::Matrix& GetInvViewMatrix() const;
	[[nodiscard]] virtual const DirectX::SimpleMath::Matrix& GetProjMatrix() const;
	[[nodiscard]] virtual const DirectX::SimpleMath::Matrix& GetInvProjMatrix() const;
	[[nodiscard]] const DirectX::SimpleMath::Vector3& GetPosition() const;

	void SetActive();
	void ClearActive();
	[[nodiscard]] bool IsActive() const;

	void UpdateKeyEvent(const CKeyboardEvent& rKeyboardEvent, const bool bEnableDir);

protected:
	virtual void OnMouseEvent(const CMouseEvent& /*rMouseEvent*/) {}
	virtual void UpdatePositionOffset(DirectX::SimpleMath::Vector3& rOutOffset);

private:
	void OnKeyboardEvent(const CKeyboardEvent& rKeyboardEvent);
	void OnKeyUp(const CKeyboardEvent& rKeyboardEvent);
	void OnKeyDown(const CKeyboardEvent& rKeyboardEvent);

protected:
    DirectX::SimpleMath::Matrix m_viewMatrix = DirectX::XMMatrixIdentity();
    DirectX::SimpleMath::Matrix m_invViewMatrix = DirectX::XMMatrixIdentity();
	const DirectX::SimpleMath::Vector3 m_DefaultUp = DirectX::SimpleMath::Vector3::Zero;
	const DirectX::SimpleMath::Vector3 m_DefaultForward = DirectX::SimpleMath::Vector3::Zero;
	const DirectX::SimpleMath::Vector3 m_DefaultRight = DirectX::SimpleMath::Vector3::Zero;
	DirectX::SimpleMath::Vector3 m_vPosition = DirectX::SimpleMath::Vector3::Zero;
	float m_fMovementSpeed = 0.001f;

private:
	std::vector<bool> m_dirPress;
	DirectX::SimpleMath::Matrix m_projectionMatrix = DirectX::XMMatrixIdentity();
	DirectX::SimpleMath::Matrix m_invProjMatrix = DirectX::XMMatrixIdentity();
	CEventId m_KeyboardEventId = CEventId::GetInvalidID();
	CEventId m_MouseEventId = CEventId::GetInvalidID();
	bool m_bIsActive = false;
};

inline const DirectX::SimpleMath::Matrix& CBaseCamera::GetViewMatrix() const { return m_viewMatrix; }
inline const DirectX::SimpleMath::Matrix& CBaseCamera::GetInvViewMatrix() const { return m_invViewMatrix; }
inline const DirectX::SimpleMath::Matrix& CBaseCamera::GetProjMatrix() const { return m_projectionMatrix; }
inline const DirectX::SimpleMath::Matrix& CBaseCamera::GetInvProjMatrix() const { return m_invProjMatrix; }
inline const DirectX::SimpleMath::Vector3& CBaseCamera::GetPosition() const { return m_vPosition; }
inline void CBaseCamera::SetActive() { m_bIsActive = true; }
inline void CBaseCamera::ClearActive() { m_bIsActive = false; }
inline bool CBaseCamera::IsActive() const { return m_bIsActive; }