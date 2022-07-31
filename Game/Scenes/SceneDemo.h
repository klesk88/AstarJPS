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
	void Update(const double dDeltaTime) override;
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