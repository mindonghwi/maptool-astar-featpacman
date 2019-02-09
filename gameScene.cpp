#include "stdafx.h"
#include "gameScene.h"

GAMESCENE::GAMESCENE()
{
}

GAMESCENE::~GAMESCENE()
{
}

HRESULT GAMESCENE::init()
{
	setWindowsSize(WINSTARTX, WINSTARTY, 500, 500);

	_pMapTool = new MAPTOOL();
	_pCamera = new CAMERA();
	_pPacMan = new PACMAN();
	_pItemMgr = new ITEMMGR();

	_pMapTool->load();

	_pCamera->init(250, 250, 500, 500);
	_pCamera->settingCameraRange(0, 0, _pMapTool->getMapCountX() * _pMapTool->getTileSize(), _pMapTool->getMapCountY() * _pMapTool->getTileSize());
	
	
	_pMapTool->setCamera(_pCamera);
	_pMapTool->settingLimitRect();

	_pPacMan->setMapTool(_pMapTool);
	_pPacMan->init();
	_pPacMan->setCamera(_pCamera);

	_pCamera->setting(_pPacMan->getPosX(), _pPacMan->getPosY());

	for (int i = 0; i < 4; i++)
	{
		_pEnemy[i] = new ENEMY();
		_pEnemy[i]->setMapTool(_pMapTool);
		_pEnemy[i]->setPacMan(_pPacMan);
	}
	_pEnemy[0]->init(TILE::OBJECT::ENEMY01, IMAGEMANAGER->findImage("yellowEnemy32"));
	_pEnemy[1]->init(TILE::OBJECT::ENEMY02, IMAGEMANAGER->findImage("skyEnemy32"));
	_pEnemy[2]->init(TILE::OBJECT::ENEMY03, IMAGEMANAGER->findImage("redEnemy32"));
	_pEnemy[3]->init(TILE::OBJECT::ENEMY04, IMAGEMANAGER->findImage("pinkEnemy32"));


	_pItemMgr->setCamera(_pCamera);
	_pItemMgr->setPacMan(_pPacMan);
	_pItemMgr->setMapTool(_pMapTool);
	_pItemMgr->init();

	//_pMapTool->deleteObject();
	return S_OK;
}

void GAMESCENE::release()
{
}

void GAMESCENE::update()
{
	_pPacMan->update();
	_pCamera->setting(_pPacMan->getPosX(), _pPacMan->getPosY());


	for (int i = 0; i < 4; i++)
	{
		_pEnemy[i]->update();
	}

	_pItemMgr->update();
}

void GAMESCENE::render()
{
	_pCamera->renderinit();
	_pMapTool->render(_pCamera->getMemDC());
	_pPacMan->render(_pCamera->getMemDC());
	for (int i = 0; i < 4; i++)
	{
		_pEnemy[i]->render(_pCamera->getMemDC());
	}

	_pItemMgr->render();
	
	_pCamera->render(getMemDC());
}

void GAMESCENE::setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	//실질적으로 클라이언트 영역 크기 셋팅을 한다
	SetWindowPos(_hWnd, NULL, x, y,
		(winRect.right - winRect.left),
		(winRect.bottom - winRect.top),
		SWP_NOZORDER | SWP_NOMOVE);
}
