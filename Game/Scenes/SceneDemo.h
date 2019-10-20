#pragma once

#include <vector>

#include "../Scenes/Grid.h"
#include "../Drawables/GridDrawable.h"
#include "../Drawables/Square.h"
#include "../Entities/AStarCharacter.h"
#include "../Entities/JPSCharacter.h"
#include "../../Framework/Engine/Core/Event.h"

#if _DEBUG
#include "../Drawables/Line.h"
#endif

class CPickerEvent;

class CSceneDemo
{
private:
	enum class ePickerMode : char
	{
		EDIT_MODE = 0,
		PATHFINDING,
	};

	enum class eEditMode : int
	{
		COLLISION = 0,
		START_POINT,
		END_POINT
	};

public:
	CSceneDemo();

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
	void ImguiEditModeUpdate();

private:
	CGrid m_Grid;
	CAStarCharacter m_aStarCharacter;
	CJPSCharacter m_jpsCharacter;

	CSquare m_startSquare;
	CSquare m_endSquare;
	CEventId m_imguiEventId;
	CEventId m_pickerEventId;

	std::vector<const char*> m_editModeCombo;
	int m_iPickerCellSelected;
	int m_iEditModeIndex;
	int m_iStartPos;
	int m_iEndPos;
	ePickerMode m_pickerMode;

#if _DEBUG
private:
	CLine m_pickerLine;
	CSquare m_pickerSquare;

	bool m_bEnablePickerDebug;
#endif
};