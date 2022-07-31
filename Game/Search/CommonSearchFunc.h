#pragma once

//framework
#include "Framework/Engine/Core/Timer.h"

//game
#include "Game/Scenes/Grid.h"
#include "Game/Helpers/Helpers.h"

//std
#include <queue>
#include <stack>

#include "Framework/Utils/WindowsPlatformCompilerSetup.h"

namespace CommonSearch
{
	//use a template function which can be used both by the Jump Point Search and by
	//the AStart search. Pass in the SearchNodeType so we can generate arrays based 
	//om the type passed.
	template <class SearchType, class SearchNodeType>
	void GetFinalPath(const std::vector<SearchNodeType>& rCellDetails, const int iIndex, SearchType& rOutInput)
	{
		int destIndex = iIndex;

		std::stack<int> path;

		while (rCellDetails[destIndex].GetParentIndex() != rOutInput.GetStartIndex())
		{
			path.push(destIndex);
			destIndex = rCellDetails[destIndex].GetParentIndex();
		}

		path.push(destIndex);
		rOutInput.m_rOutPath.clear();
		rOutInput.m_rOutPath.resize(path.size());

		//store in the vector the path. the first position represents the target
		//the last where we are. In this way we can pop elements from the back
		//without resizing the array each time
		int i = static_cast<int>(rOutInput.m_rOutPath.size() - 1);
		while (!path.empty())
		{
			rOutInput.m_rOutPath[i--] = (path.top());
			path.pop();
		}
	}

	template <class SearchType, class SearchNodeType>
	void Search(SearchType& rInput)
	{
		//common implementation between Astar and JPS of the graph search. This contains 
		//callbacks based on the class passed so that we can perform the 2 algorithms while sharing 
		//the common structure

#if _DEBUG
		CTimer timer;
		timer.Start();
#endif

		std::vector<SearchNodeType> cellDetails;
		if (rInput.GetStartIndex() == rInput.GetTargetIndex())
		{
#if _DEBUG
			rInput.SetDebug(0, cellDetails);
#endif
			return;
		}

		const CGrid& rGrid = rInput.GetGrid();

		cellDetails.reserve(rGrid.GetGridCellSize());

		for (int i = 0; i < rGrid.GetGridCellSize(); i++)
		{
			cellDetails.push_back(SearchNodeType(i));
		}

		cellDetails[rInput.GetStartIndex()].SetParent(rInput.GetStartIndex());

		auto cmp = [](SearchNodeType* left, SearchNodeType* right)->bool {
			return left->Getf() > right->Getf();
		};

		SearchNodeType& rStartNode = cellDetails[rInput.GetStartIndex()];
		rStartNode.SetParent(rInput.GetStartIndex());
		rStartNode.SetHScore(0.f);
		rStartNode.SetGScore(0.f);

		std::vector<SearchNodeType*> container;
		container.reserve(rGrid.GetGridCellSize());
		std::priority_queue<SearchNodeType*, std::vector<SearchNodeType*>, decltype(cmp)> openSet(cmp, std::move(container));
		openSet.push(&cellDetails[rInput.GetStartIndex()]);

		std::vector<int> newNodesInexes;
		newNodesInexes.reserve(rInput.GetExpectedNewCellsCountPerIter());

		int endX, endY;
		rGrid.GetCellXYFromIndex(rInput.GetTargetIndex(), endX, endY);

		int iNeighbourX, iNeighbourY;
		int iCurrentCellX, iCurrentCellY;

		while (!openSet.empty())
		{
			SearchNodeType& rCurrentCell = *(openSet.top());
			if (rCurrentCell.GetIndex() == rInput.GetTargetIndex())
			{
				GetFinalPath<SearchType, SearchNodeType>(cellDetails, rCurrentCell.GetIndex(), rInput);
				break;
			}

			openSet.pop();
			rCurrentCell.ClearIsInOpenSet();
			rCurrentCell.SetInCloseSet();

			rGrid.GetCellXYFromIndex(rCurrentCell.GetIndex(), iCurrentCellX, iCurrentCellY);
			newNodesInexes.clear();
			rInput.FindNeighbours(rCurrentCell, cellDetails, newNodesInexes);
			for (const int iNeighbourCell : newNodesInexes)
			{
				if (cellDetails[iNeighbourCell].IsInClosedSet())
				{
					continue;
				}

				rGrid.GetCellXYFromIndex(iNeighbourCell, iNeighbourX, iNeighbourY);

				const float fGNew = rCurrentCell.GetGScore() + Helpers::GetEuclideanDistance(iCurrentCellX, iCurrentCellY, iNeighbourX, iNeighbourY);

				if (fGNew >= cellDetails[iNeighbourCell].GetGScore())
				{
					continue;
				}

				const float fHNew = rInput.m_ComputeHValueFunc(endX, endY, iNeighbourX, iNeighbourY);

				cellDetails[iNeighbourCell].SetGScore(fGNew);
				cellDetails[iNeighbourCell].SetHScore(fHNew);
				cellDetails[iNeighbourCell].SetParent(rCurrentCell.GetIndex());

				if (cellDetails[iNeighbourCell].IsInOpendSet())
				{
					continue;
				}

				openSet.push(&cellDetails[iNeighbourCell]);
				cellDetails[iNeighbourCell].SetIsInOpenSet();
			}
		}

#if _DEBUG
		timer.Stop();
		rInput.SetDebug(timer.GetDeltaTime(), cellDetails);
#endif
	}
}