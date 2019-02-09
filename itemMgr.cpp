#include "stdafx.h"
#include "itemMgr.h"

ITEMMGR::ITEMMGR()
{
}

ITEMMGR::~ITEMMGR()
{
}

void ITEMMGR::init()
{
	bool bIsItem = false;

	int nPosX = 0;
	int nPosY = 0;

	bIsItem = _pMapTool->getItemPos(&nPosX, &nPosY);
	while (bIsItem) {
		_vItem.push_back(new ITEM());
		_vItem.back()->init(nPosX, nPosY, IMAGEMANAGER->findImage("item"));
		bIsItem = _pMapTool->getItemPos(&nPosX, &nPosY);
	}
	
}

void ITEMMGR::update()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, _vItem[i]->getRect(),&RectMakeCenter(_pPacman->getPosX(), _pPacman->getPosY(),30,30)))
		{
			ITEM* pItem = _vItem[i];
			pItem->release();
			delete pItem;
			pItem = nullptr;
			break;
		}
	}

}

void ITEMMGR::release()
{
	
}

void ITEMMGR::render()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->render(_pCamera->getMemDC(),
			_pCamera->getLimitRect().left, _pCamera->getLimitRect().right, _pCamera->getLimitRect().top, _pCamera->getLimitRect().bottom);
	}
}
