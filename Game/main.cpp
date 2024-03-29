#include "Framework/Engine/common_includes.h"
#include "Framework/Engine/Engine.h"
#include "Game/Scenes/SceneDemo.h"

//std
#include <memory>

//this should probably come from a config file
std::unique_ptr<CSceneDemo> GetStartScene()
{
	return std::make_unique<CSceneDemo>();
}

int main()
{
	CEngine engine;
	if (!engine.Init())
	{
		return 0;
	}

	engine.GetGameManager().AddScene(GetStartScene());
	engine.Run();

	return 0;
}