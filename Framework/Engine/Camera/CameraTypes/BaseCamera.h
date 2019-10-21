#pragma once

#include <vector>

#include "../../Core/Event.h"
#include "../../Core/SimpleMath.h"

class CConfig;
class CInputManager;
class CKeyboardEvent;
class CMouseEvent;

class CBaseCamera
{
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
	CBaseCamera(const CConfig& rConfig, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& defaultUp, const DirectX::SimpleMath::Vector3& defaultFwd, const DirectX::SimpleMath::Vector3& defaultRight, CInputManager& rInputManager);
	
public:
	virtual ~CBaseCamera();

public:
	virtual void Update() = 0;

	void Shutdown(CInputManager& rInputManager);

	const DirectX::SimpleMath::Matrix& GetViewMatrix() const { return m_viewMatrix; }
	const DirectX::SimpleMath::Matrix& GetInvViewMatrix() const { return m_invViewMatrix; }
	virtual const DirectX::SimpleMath::Matrix& GetProjMatrix() const { return m_projectionMatrix; }
	virtual const DirectX::SimpleMath::Matrix& GetInvProjMatrix() const { return m_invProjMatrix; }
	const DirectX::SimpleMath::Vector3& GetPosition() const { return m_vPosition; }

	void SetActive() { m_bIsActive = true; }
	void ClearActive() { m_bIsActive = false; }
	bool IsActive() const { return m_bIsActive; }

protected:
	virtual void OnMouseEvent(const CMouseEvent& rMouseEvent) {}
	virtual void UpdateKeyEvent(const CKeyboardEvent& rKeyboardEvent, const bool bEnableDir) = 0;
	virtual void UpdatePositionOffset(DirectX::SimpleMath::Vector3& rOutOffset);

private:
	void OnKeyboardEvent(const CKeyboardEvent& rKeyboardEvent);
	void OnKeyUp(const CKeyboardEvent& rKeyboardEvent);
	void OnKeyDown(const CKeyboardEvent& rKeyboardEvent);

protected:
	const DirectX::SimpleMath::Vector3 m_DefaultUp;
	const DirectX::SimpleMath::Vector3 m_DefaultForward;
	const DirectX::SimpleMath::Vector3 m_DefaultRight;
	DirectX::SimpleMath::Matrix m_viewMatrix;
	DirectX::SimpleMath::Matrix m_invViewMatrix;
	DirectX::SimpleMath::Vector3 m_vPosition;
	std::vector<bool> m_dirPress;
	float m_fMovementSpeed;

private:
	DirectX::SimpleMath::Matrix m_projectionMatrix;
	DirectX::SimpleMath::Matrix m_invProjMatrix;
	CEventId m_KeyboardEventId;
	CEventId m_MouseEventId;
	bool m_bIsActive;
};