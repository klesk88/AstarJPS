#pragma once

//framework
#include "Framework/Engine/Core/Event.h"
#include "Framework/Engine/Scene/SceneBase.h"

//game
#include "Game/Scenes/Grid.h"
#include "Game/Drawables/GridDrawable.h"
#include "Game/Drawables/Square.h"
#include "Game/Entities/AStarCharacter.h"
#include "Game/Entities/JPSCharacter.h"

//std
#include <vector>

#if _DEBUG
#include "Game/Drawables/Line.h"
#endif

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

class CPickerEvent;

class CSceneDemo final : public CSceneBase
{
private:
	enum class ePickerMode : char
	{
		LEGEND = 0,
		EDIT_MODE,
		PATHFINDING,
	};

	enum class eEditMode : char
	{
		COLLISION = 0,
		START_POINT,
		END_POINT
	};

public:
	CSceneDemo();
	~CSceneDemo();

	//CSceneBase
	void Init() override;
	void Shutdown() override;
	//this updates the rendering of the pathfinding result
	void Update(const float fDeltaTimeSec) override;
	//CSceneBase

private:
	void GenerateGridDesc();
	void OnPickerEvent(const CPickerEvent& rPickerEvent);
	void OnImguiUpdate();

	void UpdateImgui();
	void UpdateEditMode();
	void UpdatePathFindingMode();

	void ImguiStartPathfinding();
	void ImguiClearPathfinding();
	void ImguiModeSelection();
	void ImguiLegendMode();
	void ImguiEditModeUpdate();

private:
	CGrid m_Grid;
	CAStarCharacter m_aStarCharacter;
	CJPSCharacter m_jpsCharacter;

	CSquare m_startSquare;
	CSquare m_endSquare;
	CEventId m_imguiEventId = CEventId::GetInvalidID();
	CEventId m_pickerEventId = CEventId::GetInvalidID();

	std::vector<const char*> m_editModeCombo;
	//after a pathfinding has been request, update the rendering every second
	static constexpr float m_fMaxWaitToUpdateRendering = 1.f;
	//after a pathfinding has been request, accumulate in this variable how much time has passed since last rendering
	float m_fLastUpdateTime = m_fMaxWaitToUpdateRendering;
	int m_iPickerCellSelected = -1;
	int m_iEditModeIndex = 0;
	int m_iStartPos = 0;
	int m_iEndPos = 0;
	ePickerMode m_pickerMode = ePickerMode::LEGEND;
	bool m_bAllowEntityUpdate = false;

#if _DEBUG
private:
	CLine m_pickerLine;
	CSquare m_pickerSquare;

	bool m_bEnablePickerDebug = false;
#endif
};