#include "stdafx.h"
#include "aStarSecond.h"

ASTARTSECOND::ASTARTSECOND()
{
}

ASTARTSECOND::~ASTARTSECOND()
{
}

void ASTARTSECOND::init(int nSearchLength)
{
	_nSearchLength = nSearchLength;
	if (_nSearchLength > 8)
	{
		_nSearchLength = 8;
	}
}

void ASTARTSECOND::startFinder(int nStartIndexX, int nStartIndexY, int nEndIndexX, int nEndIndexY)
{
	//시작점을 만든다.
	//부모노드는 없다
	//시작 중심점을 잡는다.
	//코스트를 계산한다.
	_nStartIndexX = nStartIndexX;
	_nStartIndexY = nStartIndexY;
	_nEndIndexX = nEndIndexX;
	_nEndIndexY = nEndIndexY;
	
	release();

	//시작 노드 만들기
	TILENODE* pNode = new TILENODE();
	pNode->nIndexX = _nStartIndexX;
	pNode->nIndexY = _nStartIndexY;
	pNode->nPathCurrentToEnd = 0;
	pNode->nPathStartToCurrent = 0;
	pNode->nPathToatalCost = 0;
	pNode->parrentNode = nullptr;

	//열린 좌표에 넣는데 우선순위를 주자
	_listOpendNode.push_back(pNode);
}

void ASTARTSECOND::pathFinder()
{
	//8점의 좌표를 탐색
	//열린좌표에 넣는데
	//열린 좌표에 넣는데 우선순위를 주자
	//닫힌 좌표에 있으면 넣지 않는다.
	//열린좌표에 같은 값이 있으면 코스트를 비교하여 작은 애한테 부모와 코스트를 바꾸어서 대입
	//앤드면 이제 부모들을 쭉 불러와서 길을 만든다.. 이건 메이크 패스
	//앤드가 아니면 다시 재귀적으로 돌린다.
	TILENODE* pNode = _listOpendNode.front();
	_listClosedyPath.push_back(pNode);
	_listOpendNode.pop_front();

	//8점 좌표탐색
	for (int i = 0; i < _nSearchLength; i++)
	{
		int nIntervalPosX = pNode->nIndexX + _arInterval[i][static_cast<int>(POS::POSX)];
		int nIntervalPosY = pNode->nIndexY + _arInterval[i][static_cast<int>(POS::POSY)];
		
		if (nIntervalPosX < 0) continue;
		if (nIntervalPosY < 0) continue;
		if (nIntervalPosX >= _nTileSizeX) continue;
		if (nIntervalPosY >= _nTileSizeY) continue;
		//나중가서는 터리안이나 오브젝트로 처리
		if (_pMapTool->getTile(nIntervalPosX, nIntervalPosY)->getIsWall()) continue;

		bool bIsSearch = false;
		list<TILENODE*>::iterator iter = _listOpendNode.begin();
		list<TILENODE*>::iterator end = _listOpendNode.end();
		//////////open에 있으면 
		while(iter != end)
		{
			if ((*iter)->nIndexX == nIntervalPosX && (*iter)->nIndexY == nIntervalPosY) 
			{
				if ((*iter)->nPathStartToCurrent > pNode->nPathStartToCurrent + _arHuristic[i])
				{
					//바꾸고 다시 정렬해야한다.
					(*iter)->nPathStartToCurrent = pNode->nPathStartToCurrent + _arHuristic[i];
					(*iter)->nPathCurrentToEnd = abs((*iter)->nIndexX - _nEndIndexX) + abs((*iter)->nIndexY - _nEndIndexY);
					(*iter)->nPathToatalCost = (*iter)->nPathStartToCurrent + (*iter)->nPathCurrentToEnd;
					TILENODE* pOpenNode = new TILENODE;
					pOpenNode->nIndexX = nIntervalPosX;
					pOpenNode->nIndexY = nIntervalPosY;
					pOpenNode->nPathStartToCurrent = pNode->nPathStartToCurrent + _arHuristic[i];
					pOpenNode->nPathCurrentToEnd  = abs(nIntervalPosX - _nEndIndexX) + abs(nIntervalPosY - _nEndIndexY);
					pOpenNode->nPathCurrentToEnd = pOpenNode->nPathCurrentToEnd * 10;
					pOpenNode->nPathToatalCost = pOpenNode->nPathStartToCurrent + pOpenNode->nPathCurrentToEnd;
					pOpenNode->parrentNode = pNode;

					TILENODE* pTmp = *iter;
					_listOpendNode.erase(iter);
					delete pTmp;
					pTmp = nullptr;
					iter = _listOpendNode.begin();
					while ((*iter)->nPathToatalCost < pOpenNode->nPathToatalCost) {
						iter++;
					}
					_listOpendNode.insert(iter, pOpenNode);
				}								 				

				bIsSearch = true;
				break;
			}
			iter++;
		}
		if (bIsSearch) continue;
		bIsSearch = false;
		//클로즈에 있으면 넘겨야한다.
		iter = _listClosedyPath.begin();
		end = _listClosedyPath.end();
		while (iter != end) 
		{
			
			if ((*iter)->nIndexX == nIntervalPosX && (*iter)->nIndexY == nIntervalPosY) {
				bIsSearch = true;
				break;
			}
			iter++;
		}
		if (bIsSearch) continue;

		TILENODE* pOpenNode = new TILENODE;
		pOpenNode->nIndexX = nIntervalPosX;
		pOpenNode->nIndexY = nIntervalPosY;
		pOpenNode->nPathStartToCurrent = pNode->nPathStartToCurrent + _arHuristic[i];
		pOpenNode->nPathCurrentToEnd = abs(nIntervalPosX - _nEndIndexX) + abs(nIntervalPosY - _nEndIndexY);
		pOpenNode->nPathCurrentToEnd = pOpenNode->nPathCurrentToEnd * 10;
		pOpenNode->nPathToatalCost = pOpenNode->nPathStartToCurrent + pOpenNode->nPathCurrentToEnd;
		pOpenNode->parrentNode = pNode;

		if (nIntervalPosX == _nEndIndexX && nIntervalPosY == _nEndIndexY)
		{
			//찾았다
			_listMaximumPath.push_front(pOpenNode);
			_pMapTool->getTile(pOpenNode->nIndexX, pOpenNode->nIndexY)->settingTile(28, 0, false, _obj);

			TILENODE* pTmp = pOpenNode->parrentNode;
			while (pTmp != nullptr) {
				_listMaximumPath.push_front(pTmp);
				_pMapTool->getTile(pTmp->nIndexX, pTmp->nIndexY)->settingTile(28, 0, false, _obj);

				pTmp = pTmp->parrentNode;
			}
			//탈출
			return;
		}
		else
		{
			iter = _listOpendNode.begin();
			while (iter != _listOpendNode.end() &&(*iter)->nPathToatalCost < pOpenNode->nPathToatalCost) {
				iter++;
			}
			_listOpendNode.insert(iter, pOpenNode);
		}

	}

	if (_listClosedyPath.size() > 300)
	{
		//너무 많은 노드를 찾았는데도 못찾을 경우다!!
		while (!_listClosedyPath.empty())
		{
			TILENODE* pNode = _listClosedyPath.back();
			_listClosedyPath.pop_back();
			_listMaximumPath.push_front(pNode);
		}
		return;
	}

	pathFinder();
}


void ASTARTSECOND::setMapTool(MAPTOOL * pMapTool)
{
	_pMapTool = pMapTool;
	_nTileSizeX = _pMapTool->getMapCountX();
	_nTileSizeY = _pMapTool->getMapCountY();
}

void ASTARTSECOND::setObject(TILE::OBJECT obj)
{
	_obj = obj;
}

void ASTARTSECOND::release()
{
	while (!_listOpendNode.empty())
	{
		TILENODE* pNode = _listOpendNode.back();
		_listOpendNode.pop_back();
		pNode->parrentNode = nullptr;
		delete pNode;
		pNode = nullptr;
	}
	while (!_listClosedyPath.empty())
	{
		TILENODE* pNode = _listClosedyPath.back();
		_listClosedyPath.pop_back();
		pNode->parrentNode = nullptr;
		delete pNode;
		pNode = nullptr;
	}
	if(!_listMaximumPath.empty())
	{
		TILENODE* pNode = _listMaximumPath.back();
		_listMaximumPath.pop_back();
		if (pNode != nullptr)
		{
			pNode->parrentNode = nullptr;
			delete pNode;
			pNode = nullptr;
		}
		_listMaximumPath.clear();
	}



}

ASTARTSECOND::TILENODE * ASTARTSECOND::getTileNode()
{
	return nullptr;
}

void ASTARTSECOND::getNextTile(int * nX, int * nY)
{
}

ASTARTSECOND::TILENODE * ASTARTSECOND::getNode(int nIndex)
{
	list<TILENODE*>::iterator iter = _listMaximumPath.begin();
	for (int i = 0; i < nIndex; i++)
	{
		iter++;
	}

	return *iter;
}
