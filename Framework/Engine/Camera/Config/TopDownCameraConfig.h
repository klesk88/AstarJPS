#pragma once

//framework
#include "Framework/Engine/Camera/CameraTypes/TopDownCamera.h"
#include "Framework/Engine/Camera/Config/CameraConfigBase.h"

class CWindowConfig;

class CTopDownCameraConfig final : public CCameraConfigBase
{
public:
    CTopDownCameraConfig() = default;
    ~CTopDownCameraConfig() = default;

    void Load() override;
    [[nodiscard]] std::unique_ptr<CBaseCamera> GetCameraInstance(const CWindowConfig& rWindowConfig) const override;

    [[nodiscard]] float GetWheelScale() const;

private:
    const float m_fWheelScale = 0.01f;
};

inline void CTopDownCameraConfig::Load() {}
inline std::unique_ptr<CBaseCamera> CTopDownCameraConfig::GetCameraInstance(const CWindowConfig& rWindowConfig) const { return std::make_unique<CTopDownCamera>(rWindowConfig, *this); }
inline float CTopDownCameraConfig::GetWheelScale() const { return m_fWheelScale; }
