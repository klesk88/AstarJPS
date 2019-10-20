#include "SceneDemo.h"

#include <DirectXColors.h>

#include "../../Framework/Engine/Engine.h"
#include "../../Framework/Engine/Collision/CollisionHelpers.h"
#include "../../Framework/Utils/DebugMacros.h"
#include "../../Framework/Utils/Imgui/imgui.h"
#include "../../Framework/Utils/Picker/Picker.h"
#include "../../Framework/Utils/Picker/PickerEvent.h"

using namespace DirectX::SimpleMath;

CSceneDemo::CSceneDemo()
	: m_aStarCharacter(m_Grid)
	, m_jpsCharacter(m_Grid)
	, m_iPickerCellSelected(-1)
	, m_iEditModeIndex(0)
	, m_iStartPos(0)
	, m_iEndPos(0)
	, m_pickerMode(ePickerMode::EDIT_MODE)
{
	GenerateGridDesc();
	CEngine* pEngine = CEngine::GetInstance();

	m_pickerEventId = pEngine->GetPicker().PickerEvent.Attach([this](const CPickerEvent& rEvent) { OnPickerEvent(rEvent); });
	m_imguiEventId = pEngine->GetRenderer().GetImguiEventHandler().Attach([this]() { OnImguiUpdate(); });

	m_startSquare.AddSingleSquare(0, 0, m_Grid.GetCellSize(), Color(DirectX::Colors::Green));
	m_endSquare.AddSingleSquare(0, 0, m_Grid.GetCellSize(), Color(DirectX::Colors::Red));

	m_startSquare.Init();
	m_endSquare.Init();

#if _DEBUG
	m_bEnablePickerDebug = false;
#endif
}

void CSceneDemo::GenerateGridDesc()
{
	m_Grid.Init();
}

void CSceneDemo::OnPickerEvent(const CPickerEvent& rPickerEvent)
{
	m_iPickerCellSelected = -1;

#if _DEBUG
	if (m_bEnablePickerDebug)
	{
		m_pickerLine.Clear();
		m_pickerLine.AddLine(rPickerEvent.GetStartPos(), rPickerEvent.GetEndPos(), Color(DirectX::Colors::Black));
		m_pickerLine.Init();
	}
#endif

	const Vector3 boxMin(m_Grid.GetMin());
	const Vector3 boxMax(m_Grid.GetMax());
	Vector3 rayDir = rPickerEvent.GetEndPos() - rPickerEvent.GetStartPos();
	rayDir.Normalize();

	float fDistance = 0.f;
	if (!CollisionHelpers::IsRayIntersectingCube(rPickerEvent.GetStartPos(), rayDir, boxMin, boxMax, fDistance))
	{
		DEBUG_ONLY(m_pickerSquare.Reset());
		m_iPickerCellSelected = -1;
		return;
	}

	Vector3 result = rPickerEvent.GetStartPos() + (rayDir * fDistance);

	const int iX = (int)(result.x / m_Grid.GetCellSize());
	const int iZ = (int)(result.z / m_Grid.GetCellSize());

	m_iPickerCellSelected = m_Grid.GetIndexFromXY(iX, iZ);

#if _DEBUG
	if (m_bEnablePickerDebug)
	{
		m_pickerSquare.Clear();
		m_pickerSquare.AddSingleSquare(iX, iZ, m_Grid.GetCellSize(), Color(DirectX::Colors::Green));
		m_pickerSquare.Init();
	}
#endif
}

void CSceneDemo::OnImguiUpdate()
{
	ImguiModeSelection();
	UpdateImgui();
}

void CSceneDemo::UpdateImgui()
{
	switch (m_pickerMode)
	{
	case ePickerMode::EDIT_MODE:
		UpdateEditMode();
		break;
	case ePickerMode::PATHFINDING:
		UpdatePathFindingMode();
		break;
	}
}

void CSceneDemo::UpdateEditMode()
{
	if (m_iPickerCellSelected == -1)
	{
		return;
	}

	switch ((eEditMode)m_iEditModeIndex)
	{
	case eEditMode::COLLISION:
		m_Grid.CollisionUpdateFromPicker(m_iPickerCellSelected);
		break;
	case eEditMode::START_POINT:
		if (m_iStartPos != m_iPickerCellSelected)
		{
			m_Grid.RemoveCollisionIfNeeded(m_iPickerCellSelected);
			m_startSquare.Clear();
			m_iStartPos = m_iPickerCellSelected;

			int iX, iY;
			m_Grid.GetCellXYFromIndex(m_iPickerCellSelected, iX, iY);
			Color color(DirectX::Colors::Green);
			color.w = 0.4f;
			m_startSquare.AddSingleSquare(iX, iY, m_Grid.GetCellSize(), color);
			m_startSquare.Init();
		}

		break;
	case eEditMode::END_POINT:
		if (m_iEndPos != m_iPickerCellSelected)
		{
			m_Grid.RemoveCollisionIfNeeded(m_iPickerCellSelected);
			m_iEndPos = m_iPickerCellSelected;
			m_endSquare.Clear();

			int iX, iY;
			m_Grid.GetCellXYFromIndex(m_iEndPos, iX, iY);
			Color color(DirectX::Colors::Red);
			color.w = 0.3f;
			m_endSquare.AddSingleSquare(iX, iY, m_Grid.GetCellSize(), color);
			m_endSquare.Init();;
		}
		break;
	default:
		return;
	}

	m_iPickerCellSelected = -1;
}

void CSceneDemo::UpdatePathFindingMode()
{
	DEBUG_ONLY(ImGui::Checkbox("Display Picker Debug", &m_bEnablePickerDebug));

	ImguiStartPathfinding();
	ImguiClearPathfinding();

#if _DEBUG
	m_aStarCharacter.UpdateImgui();
	m_jpsCharacter.UpdateImgui();
#endif
}

void CSceneDemo::ImguiStartPathfinding()
{
	if (!ImGui::Button("Start Pathfinding"))
	{
		return;
	}

	if (m_iStartPos == -1 || m_iEndPos == -1)
	{
		return;
	}

	m_aStarCharacter.Clear();
	m_jpsCharacter.Clear();

	m_aStarCharacter.Init(m_iStartPos, m_iEndPos);
	m_jpsCharacter.Init(m_iStartPos, m_iEndPos);

	if (!m_aStarCharacter.IsEnable())
	{
		m_aStarCharacter.SetEnable(true);
	}

	if (!m_jpsCharacter.IsEnable())
	{
		m_jpsCharacter.SetEnable(true);
	}
}

void CSceneDemo::ImguiClearPathfinding()
{
	if (!ImGui::Button("Clear Pathfinding"))
	{
		return;
	}

	m_aStarCharacter.SetEnable(false);
	m_jpsCharacter.SetEnable(false);
}

void CSceneDemo::ImguiModeSelection()
{
	if (ImGui::RadioButton("EDIT_MODE", m_pickerMode == ePickerMode::EDIT_MODE))
	{
		m_pickerMode = ePickerMode::EDIT_MODE;
		m_iPickerCellSelected = -1;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("PATHFINDING", m_pickerMode == ePickerMode::PATHFINDING))
	{
		m_pickerMode = ePickerMode::PATHFINDING;
		m_iPickerCellSelected = -1;
	}

	switch (m_pickerMode)
	{
	case ePickerMode::EDIT_MODE:
		ImguiEditModeUpdate();
		break;
	case ePickerMode::PATHFINDING:
		break;
	}
}

void CSceneDemo::ImguiEditModeUpdate()
{
	const char* desc[] =
	{
		"Collision",
		"Start Point",
		"Target Point",
	};

	ImGui::Combo("Mode", &m_iEditModeIndex, desc, IM_ARRAYSIZE(desc));
}
