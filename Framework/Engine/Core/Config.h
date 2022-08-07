#pragma once

#include "Framework/Engine/Camera/CameraManagerConfig.h"
#include "Framework/Engine/Core/ConfigBase.h"
#include "Framework/Engine/Core/WindowConfig.h"

//directx
#include <directxmath.h>

//std
#include <memory>
#include <vector>

class CCameraConfigBase;

//simple config class which can is used to store base data
//which could be stored in a .ini file and be changed by the user
//and loaded at startup or once the game have been loaded
class CConfig final : public CConfigBase
{
public:
	CConfig();
	~CConfig();

	void Load() override;

	[[nodiscard]] const CWindowConfig& GetWindowConfig() const;
	[[nodiscard]] const CCameraManagerConfig& GetCameraManagerConfig() const;
	[[nodiscard]] const std::vector<std::unique_ptr<CCameraConfigBase>>& GetCameraConfigs() const;

private:
	void LoadCameraData();

private:
	CWindowConfig mWindowConfig;
	CCameraManagerConfig mCameraManagerConfig;
	std::vector<std::unique_ptr<CCameraConfigBase>> mCamerasConfig;
};

inline const CWindowConfig& CConfig::GetWindowConfig() const { return mWindowConfig; }
inline const CCameraManagerConfig& CConfig::GetCameraManagerConfig() const { return mCameraManagerConfig; }
inline const std::vector<std::unique_ptr<CCameraConfigBase>>& CConfig::GetCameraConfigs() const { return mCamerasConfig; }
