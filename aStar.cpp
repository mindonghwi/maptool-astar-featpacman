#include "stdafx.h"
//#include "aStar.h"
//#include "mapTool.h"
//
//ASTAR::ASTAR()
//{
//}
//
//ASTAR::~ASTAR()
//{
//}
//
//void ASTAR::init()
//{
//}
//
//void ASTAR::startFinder(int nStartIndexX, int nStartIndexY, int nEndIndexX, int nEndIndexY)
//{
//	_nStartPosX = nStartIndexX;
//	_nStartPosY = nStartIndexY;
//	_nEndIndexX = nEndIndexX;
//	_nEndIndexY = nEndIndexY;
//	
//	while (!_listMaximumPath.empty()) {
//		TILENODE* pTileNode = _listMaximumPath.back();
//		_listMaximumPath.pop_back();
//		delete pTileNode;
//		pTileNode = nullptr;
//	}
//
//
//}
//
//void ASTAR::pathFinder(int nCurrentIndexX, int nCurrentIndexY)
//{
//	if (nCurrentIndexX == _nEndIndexX && nCurrentIndexY == _nEndIndexY)
//	{
//		makePath();
//		return;
//	}
//	
//	bool bIsFind = false;
//	//8방향 
//	for (int i = 0; i < 8; i++)
//	{
//		int nIntervalPosX = nCurrentIndexX + _arInterval[i][static_cast<int>(POS::POSX)];
//		int nIntervalPosY = nCurrentIndexY + _arInterval[i][static_cast<int>(POS::POSY)];
//		int nTemp = 10;
//		if (nIntervalPosX < 0) continue;
//		if (nIntervalPosY < 0) continue;
//		if (nIntervalPosX >= _nTileSizeX) continue;
//		if (nIntervalPosY >= _nTileSizeY) continue;
//		
//		//나중가서는 터리안이나 오브젝트로 처리
//		if (_pMapTool->getTile(nIntervalPosX, nIntervalPosY)->getIsWall()) continue;
//		
//
//		int nStartToCurrent = abs(_nStartPosX - nIntervalPosX) + abs(_nStartPosY - nIntervalPosY);
//		int	nEndToCurrent = abs(_nEndIndexX - nIntervalPosX) + abs(_nEndIndexY - nIntervalPosY);
//
//		TILENODE* sTileNode = new TILENODE();
//		sTileNode->nIndexX = nIntervalPosX;
//		sTileNode->nIndexY = nIntervalPosY;
//		
//		bool bIsCheck = false;
//		
//		for (int i = 0; i < _vX.size(); i++)
//		{
//			if (nIntervalPosX == _vX[i] && nIntervalPosY == _vY[i]) {
//				bIsCheck = true;
//				break;
//			}
//		}
//		
//		if (i > 3)
//		{
//			nTemp = 14;
//		}
//		sTileNode->nPathCost = (nStartToCurrent + nEndToCurrent) * nTemp;
//
//		if (sTileNode->nPathCost > 5000)
//		{
//			makePath();
//			return;
//		}
//
//		if (nEndToCurrent == 0)
//		{
//			_stackPriorityPath.push(sTileNode);
//			bIsFind = true;
//
//		}
//		if (!bIsCheck)
//		{
//			_queSearchedNode.push(sTileNode);
//			_vX.push_back(sTileNode->nIndexX);
//			_vY.push_back(sTileNode->nIndexY);
//		}
//
//		if (nIntervalPosX == _nEndIndexX && nIntervalPosY == _nEndIndexY)
//		{
//			makePath();
//			return;
//		}
//	}
//
//
//
//	if (bIsFind)
//	{
//		makePath();
//		return;
//	}
//
//	if (!_queSearchedNode.empty()) {
//		make_heap(const_cast<TILENODE**>(&_queSearchedNode.top()), const_cast<TILENODE**>(&_queSearchedNode.top()) + _queSearchedNode.size(),
//			CompareNode());
//
//		_stackPriorityPath.push(_queSearchedNode.top());
//		_queSearchedNode.pop();
//	}
//
//
//
//	if (_stackPriorityPath.size() > 500)
//	{
//		makePath();
//		return;
//	}
//
//	pathFinder(_stackPriorityPath.top()->nIndexX, _stackPriorityPath.top()->nIndexY);
//}
////찾은경우
//void ASTAR::makePath()
//{
//	//큐에 있는 데이터 빼기
//	while (!_queSearchedNode.empty())
//	{
//		TILENODE* pTileNode = _queSearchedNode.top();
//		_queSearchedNode.pop();
//		delete pTileNode;
//		pTileNode = nullptr;
//	}
//
//	//리스트에 담기
//	_listMaximumPath.push_front(_stackPriorityPath.top());
//	_stackPriorityPath.pop();
//	while (!_stackPriorityPath.empty())
//	{
//		TILENODE* pTileNode = _listMaximumPath.front();
//		_listMaximumPath.push_front(_stackPriorityPath.top());
//		_stackPriorityPath.pop();
//
//		int nOffset = abs(pTileNode->nIndexX - _listMaximumPath.front()->nIndexX) + abs(pTileNode->nIndexY - _listMaximumPath.front()->nIndexY);
//		if (nOffset > 2)
//		{
//			_listMaximumPath.pop_front();
//		}
//	}
//
//	for (int i = 0; !_listMaximumPath.empty(); i++)
//	{
//		_pMapTool->getTile(_listMaximumPath.front()->nIndexX, _listMaximumPath.front()->nIndexY)->settingTile(28, 0, false, TILE::ENEMY01);
//		_listMaximumPath.pop_front();
//	}
//}
//
////찾다가 못찾을 경우
//void ASTAR::makeFailPath()
//{
//	//큐에 있는 데이터 빼기
//	while (!_queSearchedNode.empty())
//	{
//		TILENODE* pTileNode = _queSearchedNode.top();
//		_queSearchedNode.pop();
//		delete pTileNode;
//		pTileNode = nullptr;
//	}
//
//	//리스트에 담기
//	while (!_stackPriorityPath.empty())
//	{
//		_listMaximumPath.push_front(_stackPriorityPath.top());
//		_stackPriorityPath.pop();
//	}
//
//}
//
//void ASTAR::setMapTool(MAPTOOL * pMapTool)
//{
//	_pMapTool = pMapTool;
//	_nTileSizeX = _pMapTool->getMapCountX();
//	_nTileSizeY = _pMapTool->getMapCountY();
//}
//
//void ASTAR::release()
//{
//	while (!_queSearchedNode.empty())
//	{
//		TILENODE* pTileNode = _queSearchedNode.top();
//		_queSearchedNode.pop();
//		delete pTileNode;
//		pTileNode = nullptr;
//	}
//
//	//리스트에 담기
//	while (!_stackPriorityPath.empty())
//	{
//		_listMaximumPath.push_front(_stackPriorityPath.top());
//		_stackPriorityPath.pop();
//	}
//
//	while (!_listMaximumPath.empty()) {
//		TILENODE* pTileNode = _listMaximumPath.back();
//		_listMaximumPath.pop_back();
//		delete pTileNode;
//		pTileNode = nullptr;
//	}
//}
//
