#pragma once

//framework
#include "Framework/Engine/Core/ConfigBase.h"

//directx
#include <directxmath.h>

//std
#include <memory>

class CBaseCamera;
class CInputManager;
class CWindowConfig;

class CCameraConfigBase : public CConfigBase
{
public:
    CCameraConfigBase() = default;
    ~CCameraConfigBase() = default;
    
    [[nodiscard]] virtual std::unique_ptr<CBaseCamera> GetCameraInstance(const CWindowConfig& rWindowConfig) const = 0;

    [[nodiscard]] float GetMovementSpeed() const;
    [[nodiscard]] float GetFOV() const;

protected:
    float m_fMovementSpeed = 10.f;
    float m_fFOV = DirectX::XM_PI / 4.0f;
};

inline float CCameraConfigBase::GetMovementSpeed() const { return m_fMovementSpeed; }
inline float CCameraConfigBase::GetFOV() const { return m_fFOV; }
