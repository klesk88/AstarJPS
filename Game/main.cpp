#include "../Framework/Engine/common_includes.h"
#include "../Framework/Engine/Engine.h"
#include "Scenes/SceneDemo.h"

int main()
{
	CEngine engine;
	if (!engine.Init())
	{
		return 0;
	}

	CSceneDemo aStarDemo;
	aStarDemo.Init();
	engine.GetGameManager().AddScene(aStarDemo);
	engine.Run();

	return 0;
}