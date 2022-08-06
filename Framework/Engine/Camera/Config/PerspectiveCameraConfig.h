#pragma once

//framework
#include "Framework/Engine/Camera/CameraTypes/PerspectiveCamera.h"
#include "Framework/Engine/Camera/Config/CameraConfigBase.h"

class CInputManager;
class CWindowConfig;

class CPerspectiveCameraConfig final : public CCameraConfigBase
{
public:
    CPerspectiveCameraConfig() = default;
    ~CPerspectiveCameraConfig() = default;

    void Load() override;
    [[nodiscard]] std::unique_ptr<CBaseCamera> GetCameraInstance(const CWindowConfig& rWindowConfig, CInputManager& rInputManager) const override;
};

inline void CPerspectiveCameraConfig::Load() {}
inline std::unique_ptr<CBaseCamera> CPerspectiveCameraConfig::GetCameraInstance(const CWindowConfig& rWindowConfig, CInputManager& rInputManager) const { return std::make_unique<CPerspectiveCamera>(rWindowConfig, *this, rInputManager); }