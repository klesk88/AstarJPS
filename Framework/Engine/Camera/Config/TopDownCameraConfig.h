#pragma once

//framework
#include "Framework/Engine/Camera/CameraTypes/TopDownCamera.h"
#include "Framework/Engine/Camera/Config/CameraConfigBase.h"

class CInputManager;
class CWindowConfig;

class CTopDownCameraConfig final : public CCameraConfigBase
{
public:
    CTopDownCameraConfig() = default;
    ~CTopDownCameraConfig() = default;

    void Load() override;
    [[nodiscard]] std::unique_ptr<CBaseCamera> GetCameraInstance(const CWindowConfig& rWindowConfig, CInputManager& rInputManager) const override;

    [[nodiscard]] float GetWheelScale() const;
    [[nodiscard]] float GetWheelDelta() const;

private:
    const float m_fWheelScale = 0.01f;
    const float m_fMouseWheelDelta = 0.05f;
};

inline void CTopDownCameraConfig::Load() {}
inline std::unique_ptr<CBaseCamera> CTopDownCameraConfig::GetCameraInstance(const CWindowConfig& rWindowConfig, CInputManager& rInputManager) const { return std::make_unique<CTopDownCamera>(rWindowConfig, *this, rInputManager); }
inline float CTopDownCameraConfig::GetWheelScale() const { return m_fWheelScale; }
inline float CTopDownCameraConfig::GetWheelDelta() const { return m_fMouseWheelDelta; }