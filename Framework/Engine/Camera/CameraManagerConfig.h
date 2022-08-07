#pragma once

//framework
#include "Framework/Engine/Camera/CameraTypes/CameraTypes.h"
#include "Framework/Engine/Core/ConfigBase.h"

class CCameraManagerConfig final : public CConfigBase
{
public:
    CCameraManagerConfig() = default;
    ~CCameraManagerConfig() = default;
    
    void Load() override;
    [[nodiscard]] eCameraTye GetStartCameraType() const;

protected:
    eCameraTye m_startCameraType = eCameraTye::TOP_DOWN;
};

inline void CCameraManagerConfig::Load() {}
inline eCameraTye CCameraManagerConfig::GetStartCameraType() const { return m_startCameraType; }
