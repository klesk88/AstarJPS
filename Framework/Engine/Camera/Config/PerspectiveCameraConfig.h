#pragma once

//framework
#include "Framework/Engine/Camera/CameraTypes/PerspectiveCamera.h"
#include "Framework/Engine/Camera/Config/CameraConfigBase.h"

class CWindowConfig;

class CPerspectiveCameraConfig final : public CCameraConfigBase
{
public:
    CPerspectiveCameraConfig() = default;
    ~CPerspectiveCameraConfig() = default;

    void Load() override;
    [[nodiscard]] std::unique_ptr<CBaseCamera> GetCameraInstance(const CWindowConfig& rWindowConfig) const override;
    [[nodiscard]] float GetAngularVelocityScale() const;

private:
    float m_fAngularVelocityScale = 0.1f;
};

inline void CPerspectiveCameraConfig::Load() {}
inline std::unique_ptr<CBaseCamera> CPerspectiveCameraConfig::GetCameraInstance(const CWindowConfig& rWindowConfig) const { return std::make_unique<CPerspectiveCamera>(rWindowConfig, *this); }
inline float CPerspectiveCameraConfig::GetAngularVelocityScale() const { return m_fAngularVelocityScale; }