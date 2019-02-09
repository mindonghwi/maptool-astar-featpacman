#include "stdafx.h"
#include "astarAlgorithm.h"
#include "mapTool.h"


ASTAR_ALGORITHM::ASTAR_ALGORITHM()
{
}

ASTAR_ALGORITHM::~ASTAR_ALGORITHM()
{
}

void ASTAR_ALGORITHM::init()
{
}

void ASTAR_ALGORITHM::startFinder(int nStartIndexX, int nStartIndexY, int nEndIndexX, int nEndIndexY)
{
	_nStartPosX = nStartIndexX;
	_nStartPosY = nStartIndexY;
	_nEndIndexX = nEndIndexX;
	_nEndIndexY = nEndIndexY;


	while (!_listMaximumPath.empty()) {
		TILENODE* pTileNode = _listMaximumPath.back();
		_listMaximumPath.pop_back();
		delete pTileNode;
		pTileNode = nullptr;
	}

	TILENODE* sTile = new TILENODE();
	sTile->nIndexX = _nStartPosX;
	sTile->nIndexY = _nStartPosY;
	sTile->nPathCost = 0;

	_stackPriorityPath.push(sTile);
}

void ASTAR_ALGORITHM::pathFinder(int nCurrentIndexX, int nCurrentIndexY)
{
	if (nCurrentIndexX == _nEndIndexX && nCurrentIndexY == _nEndIndexY)
	{
		makePath();
		return;
	}

	//8방향 
	for (int i = 0; i < 4; i++)
	{
		int nIntervalPosX = nCurrentIndexX + _arInterval[i][static_cast<int>(POS::POSX)];
		int nIntervalPosY = nCurrentIndexY + _arInterval[i][static_cast<int>(POS::POSY)];
		int nTemp = 10;
		if (nIntervalPosX < 0) continue;
		if (nIntervalPosY < 0) continue;
		if (nIntervalPosX >= _nTileSizeX) continue;
		if (nIntervalPosY >= _nTileSizeY) continue;
		//나중가서는 터리안이나 오브젝트로 처리
		if (_pMapTool->getTile(nIntervalPosX, nIntervalPosY)->getIsWall()) continue;


		bool bIsSearch = false;
		list<TILENODE*>::iterator iter = _listSearchedNode.begin();
		list<TILENODE*>::iterator end = _listSearchedNode.end();

		for (int i = 0; i < _vX.size(); i++)
		{
			if (_vX[i] == nIntervalPosX && _vY[i] == nIntervalPosY) {
				bIsSearch = true;
			}
		}

		if (bIsSearch) continue;
		
		int nStartToCurrent = abs(_nStartPosX - nIntervalPosX) + abs(_nStartPosY - nIntervalPosY);
		int	nEndToCurrent = abs(_nEndIndexX - nIntervalPosX) + abs(_nEndIndexY - nIntervalPosY);

		TILENODE* sTileNode = new TILENODE();
		sTileNode->nIndexX = nIntervalPosX;
		sTileNode->nIndexY = nIntervalPosY;
		
		_vX.push_back(nIntervalPosX);
		_vY.push_back(nIntervalPosY);
		sTileNode->nPathCost = ((nStartToCurrent + nEndToCurrent) * _arHuristic[i]);


		


		if (_nEndIndexX == nIntervalPosX && _nEndIndexY == nIntervalPosY)
		{
			_stackPriorityPath.push(sTileNode);
			makePath();
			return;
		}


		iter = _listSearchedNode.begin();
		end = _listSearchedNode.end();
		while (iter != end && (*iter)->nPathCost < sTileNode->nPathCost)
		{
			iter++;
		}
		_listSearchedNode.insert(iter, sTileNode);
	}

	if (!_listSearchedNode.empty())
	{
		_stackPriorityPath.push(_listSearchedNode.front());
		_listSearchedNode.pop_front();
	}

	if (_stackPriorityPath.size() > 400)
	{
		makePath();
		return;
	}
	pathFinder(_stackPriorityPath.top()->nIndexX, _stackPriorityPath.top()->nIndexY);
}

void ASTAR_ALGORITHM::makePath()
{
	//큐에 있는 데이터 빼기
	while (!_listSearchedNode.empty())
	{
		TILENODE* pTileNode = _listSearchedNode.back();
		_listSearchedNode.pop_back();
		delete pTileNode;
		pTileNode = nullptr;
	}

	//리스트에 담기
	_listMaximumPath.push_front(_stackPriorityPath.top());
	_stackPriorityPath.pop();
	while (!_stackPriorityPath.empty())
	{
		//_pMapTool->getTile(_stackPriorityPath.top()->nIndexX, _stackPriorityPath.top()->nIndexY)->setFrameX(2);

		TILENODE* pTileNode = _listMaximumPath.front();
		int nDst = pTileNode->nPathCost;
		int nSrc = _stackPriorityPath.top()->nPathCost;

		if (nSrc < nDst) {
			int nDisOld = abs(_nStartPosX - pTileNode->nIndexX) + abs(_nStartPosY - pTileNode->nIndexY);
			int nDisNew = abs(_nStartPosX - _stackPriorityPath.top()->nIndexX) + abs(_nStartPosY - _stackPriorityPath.top()->nIndexY);
			if (nDisOld < nDisNew)
			{
				_stackPriorityPath.pop();
				continue;
			}
		}
		
		_listMaximumPath.push_front(_stackPriorityPath.top());
		_stackPriorityPath.pop();

		_vX.clear();
		_vY.clear();

		int nOffset = abs(pTileNode->nIndexX - _listMaximumPath.front()->nIndexX) + abs(pTileNode->nIndexY - _listMaximumPath.front()->nIndexY);
		if (nOffset > 2)
		{
			_listMaximumPath.pop_front();
		}
	}

	list<TILENODE*>::iterator iter = _listMaximumPath.begin();
	for (int i = 0;  i <_listMaximumPath.size(); i++)
	{
		_pMapTool->getTile((*iter)->nIndexX, (*iter)->nIndexY)->settingTile(28,0,false,_obj);
		//_listMaximumPath.pop_front();
		iter++;
	}
}

void ASTAR_ALGORITHM::makeFailPath()
{
}

void ASTAR_ALGORITHM::setMapTool(MAPTOOL * pMapTool)
{
	_pMapTool = pMapTool;
	_nTileSizeX = _pMapTool->getMapCountX();
	_nTileSizeY = _pMapTool->getMapCountY();
}

void ASTAR_ALGORITHM::setObject(TILE::OBJECT obj)
{
	_obj = obj; 
}

void ASTAR_ALGORITHM::release()
{
	//큐에 있는 데이터 빼기
	while (!_listSearchedNode.empty())
	{
		TILENODE* pTileNode = _listSearchedNode.back();
		_listSearchedNode.pop_back();
		delete pTileNode;
		pTileNode = nullptr;
	}

	//리스트에 담기
	while (!_stackPriorityPath.empty())
	{
		_listMaximumPath.push_front(_stackPriorityPath.top());
		_stackPriorityPath.pop();
	}

	while (!_listMaximumPath.empty()) {
		TILENODE* pTileNode = _listMaximumPath.back();
		_listMaximumPath.pop_back();
		delete pTileNode;
		pTileNode = nullptr;
	}
}

ASTAR_ALGORITHM::TILENODE * ASTAR_ALGORITHM::getTileNode()
{
	if (_listMaximumPath.empty()) return nullptr;
	TILENODE* pTileNode = _listMaximumPath.front();
	
	return pTileNode;
}

void ASTAR_ALGORITHM::getNextTile(int * nX, int * nY)
{
	if (_listMaximumPath.empty())
	{
		return;
	}
	TILENODE* pTileNode = _listMaximumPath.front();
	*nX = pTileNode->nIndexX;
	*nY = pTileNode->nIndexY;
	_listMaximumPath.pop_front();
	delete pTileNode;
	pTileNode = nullptr;

}

