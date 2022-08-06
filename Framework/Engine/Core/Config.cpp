#include "Framework/Engine/Core/Config.h"

//framework
#include "Framework/Engine/Camera/Config/PerspectiveCameraConfig.h"
#include "Framework/Engine/Camera/Config/TopDownCameraConfig.h"

//directx
#include <directxmath.h>

//windows
#include <windows.h>

CConfig::CConfig()
{
	//construictor here so i dont need to include the camera in the .h as they are unique ptr
}

CConfig::~CConfig()
{
	//destructor here so i dont need to include the camera in the .h as they are unique ptr
}

void CConfig::Load()
{
	//TODO: we should read am actual config file here (a json probably) at some point

	LoadCameraData();
	mWindowConfig.Load();
	mCameraManagerConfig.Load();
}

void CConfig::LoadCameraData()
{
	mCamerasConfig.reserve(2);

	mCamerasConfig.push_back(std::make_unique<CTopDownCameraConfig>());
	mCamerasConfig.push_back(std::make_unique<CPerspectiveCameraConfig>());
}
