#include "GridDrawable.h"

#include <DirectXColors.h>

#include "Game/Scenes/Grid.h"

#include "Framework/Engine/Camera/CameraManager.h"
#include "Framework/Engine/Core/Config.h"
#include "Framework/Engine/Engine.h"

using namespace DirectX::SimpleMath;

CGridDrawable::CGridDrawable()
	: CColorDrawableBase(D3D_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_LINELIST, D3D11_USAGE::D3D11_USAGE_IMMUTABLE)
{
}

void CGridDrawable::InitParams(const int iSizeX, const int iSizeY, const float fCellSize, Vector3&rOutMin, Vector3& rOutMax)
{
	const int numVertexes = iSizeX * iSizeY * 6;

	m_vertexes.reserve(numVertexes);
	m_indexes.reserve(numVertexes);

	const Color color(DirectX::Colors::Black);

	const float fStartPosX = 0.f;
	const float fStartPosY= 0.f;
	for (int iY = 0; iY < iSizeY; ++iY)
	{
		for (int iX = 0; iX < iSizeX; ++iX)
		{
			const int iCurrentIndex = (iY * iSizeX) + iX;
			const float fCurrentXPos = fStartPosX + (iX * fCellSize);
			const float fCurrentYPos = fStartPosY + (iY * fCellSize);

			AddSquareLines(iX, iY, fCellSize, color);
		}
	}

	const float fMaxX = fStartPosX + (iSizeX * fCellSize);
	const float fMaxY = fStartPosY + (iSizeY * fCellSize);
	rOutMin = Vector3(fStartPosX, 0.f, fStartPosY);
	rOutMax = Vector3(fMaxX, 0.f, fMaxY);

	m_iIndexCount = static_cast<int>(m_indexes.size());
	Init();
}

void CGridDrawable::AddSquareLines(const int iStartX, const int iStartY, const float fCellSize, const Color color)
{
	const float fStartX = iStartX * fCellSize;
	const float fStartY = iStartY * fCellSize;
	const unsigned short iStartIndex = static_cast<unsigned short>(m_vertexes.size());

	AddVertex(fStartX, fStartY, 0.f, color);
	AddVertex(fStartX, fStartY + fCellSize, 0.f, color);
	AddVertex(fStartX + fCellSize, fStartY + fCellSize, 0.f, color);
	AddVertex(fStartX + fCellSize, fStartY, 0.f, color);

	m_indexes.push_back(iStartIndex);
	m_indexes.push_back(iStartIndex + 1);
	m_indexes.push_back(iStartIndex + 1);
	m_indexes.push_back(iStartIndex + 2);
	m_indexes.push_back(iStartIndex + 2);
	m_indexes.push_back(iStartIndex + 3);
	m_indexes.push_back(iStartIndex + 3);
	m_indexes.push_back(iStartIndex );
}


