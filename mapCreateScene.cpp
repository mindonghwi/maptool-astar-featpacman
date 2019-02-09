#include "stdafx.h"
#include "mapCreateScene.h"

MAPSCENE::MAPSCENE()
{
}

MAPSCENE::~MAPSCENE()
{
}

HRESULT MAPSCENE::init()
{
	_pCamera = new CAMERA();
	_pCamera->init((WINSIZEX) / 4, WINSIZEY / 2, (WINSIZEX) / 2, WINSIZEY);

	_pMapTool = new MAPTOOL();
	_pMapTool->init(20,20,32);
	_pMapTool->setCamera(_pCamera);
	IMAGEMANAGER->addFrameImage("mapTiles", "image/mapPallet.bmp", 0, 0, 256, 32, 7, 1, true, RGB(255, 0, 255));
	
	IMAGEMANAGER->addFrameImage("up", "image/up.bmp", 70, 140, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("down", "image/down.bmp", 70, 140, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("left", "image/left.bmp", 70, 140, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("right", "image/right.bmp", 70, 140, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("save", "image/btnSave.bmp", 70, 140, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("load", "image/btnLoad.bmp", 70, 140, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("btnPlayGame", "image/btnPlayGame.bmp", 60, 140, 1, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("pacman32", "image/pacman32.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("yellowEnemy32", "image/yellowEnemy32.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("skyEnemy32", "image/skyEnemy32.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("redEnemy32", "image/redEnemy32.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pinkEnemy32", "image/pinkEnemy32.bmp", 128, 64, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("item", "image/item.bmp", 32, 32,1,1, true, RGB(255, 0, 255));

	for (int i = 0; i < static_cast<int>(BTN::MAX); i++)
	{
		_btn[i] = new button();
	}
	POINT pt[2];
	pt[0].x = 0;
	pt[0].y = 0;
	pt[1].x = 0;
	pt[1].y = 1;

	_btn[static_cast<int>(BTN::MAPUP)]->init("up", 900, 500, pt[1], pt[0], bind(&MAPSCENE::callBackMapUp, this));
	_btn[static_cast<int>(BTN::MAPDOWN)]->init("down", 970, 500, pt[1], pt[0], bind(&MAPSCENE::callBackMapDown, this));
	_btn[static_cast<int>(BTN::MAPLEFT)]->init("left", 1040, 500, pt[1], pt[0], bind(&MAPSCENE::callBackMapLeft, this));
	_btn[static_cast<int>(BTN::MAPRIGHT)]->init("right", 1110, 500, pt[1], pt[0], bind(&MAPSCENE::callBackMapRight, this));
	_btnPlayGame = new button();
	_btnPlayGame->init("btnPlayGame", 1370, 500, pt[1], pt[0], bind(&MAPSCENE::callBackGotoGameScene, this));

	_btnSave = new button();
	_btnLoad = new button();
	_btnSave->init("save",1180,500,pt[1],pt[0],bind(&MAPSCENE::callBackMapSave,this));
	_btnLoad->init("load",1250,500,pt[1],pt[0],bind(&MAPSCENE::callBackMapLoad,this));


	_rcWallPallet = RectMake(WINSIZEX - (WINSIZEX) / 4, 200, IMAGEMANAGER->findImage("mapTiles")->getFrameWidth(),
		IMAGEMANAGER->findImage("mapTiles")->getFrameHeight());
	_rcPassPallet = RectMake(WINSIZEX - (WINSIZEX) / 4 + 32, 200, IMAGEMANAGER->findImage("mapTiles")->getFrameWidth(),
		IMAGEMANAGER->findImage("mapTiles")->getFrameHeight());

	int nOffset = 64;
	for (int i = 1; i < static_cast<int>(TILE::OBJECT::MAX); i++)
	{
		_arPallet[i] = RectMake(WINSIZEX - (WINSIZEX) / 4 + nOffset, 200, IMAGEMANAGER->findImage("mapTiles")->getFrameWidth(),
			IMAGEMANAGER->findImage("mapTiles")->getFrameHeight());
		nOffset += 32;
	}

	_endScene = false;

	return S_OK;
}

void MAPSCENE::release()
{
	_pMapTool->release();
	for (int i = 0; i < 4; i++)
	{
		_btn[i]->release();
	}
	_btnLoad->release();
	_btnSave->release();
	
}

void MAPSCENE::update()
{
	for (int i = 0; i < 4; i++)
	{
		_btn[i]->update();
	}
	_btnLoad->update();
	_btnSave->update();
	_btnPlayGame->update();

	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//º®°Ç¼³
		if (PtInRect(&_rcWallPallet, _ptMouse))
		{
			_pMapTool->setCurrentX(0);
			_pMapTool->setCurrentY(0);
			_pMapTool->setisWall(true);
			_pMapTool->setObject(TILE::OBJECT::NONE);
		}
		else if (PtInRect(&_rcPassPallet, _ptMouse))
		{
			_pMapTool->setCurrentX(28);
			_pMapTool->setCurrentY(0);
			_pMapTool->setisWall(false);
			_pMapTool->setObject(TILE::OBJECT::NONE);
		}
		for (int i = static_cast<int>(TILE::OBJECT::PACMAN); i < static_cast<int>(TILE::OBJECT::MAX); i++)
		{
			if (PtInRect(&_arPallet[i], _ptMouse))
			{
				_pMapTool->setCurrentX(28);
				_pMapTool->setCurrentY(0);
				_pMapTool->setisWall(false);
				_pMapTool->setObject(static_cast<TILE::OBJECT>(i));
			}
		}
	}


	if (KEYMANAGER->isDBClickLButton())
	{
		_pMapTool->setCurrentY(0);
	}
	if (KEYMANAGER->isDBClickRButton())
	{
		_pMapTool->setCurrentY(0);
	}
	if(!_endScene)
	_pMapTool->update();



}

void MAPSCENE::render()
{
	_pCamera->renderinit();

	_pMapTool->render(_pCamera->getMemDC());

	for (int i = 0; i < 4; i++)
	{
		_btn[i]->render(getMemDC());
	}
	_btnLoad->render(getMemDC());
	_btnSave->render(getMemDC());
	_btnPlayGame->render(getMemDC());
	IMAGEMANAGER->findImage("mapTiles")->render(getMemDC(), WINSIZEX - (WINSIZEX) / 4, 200);

	_pCamera->render(getMemDC());
}

void MAPSCENE::setup()
{
}

void MAPSCENE::callBackMapDown()
{
	_pMapTool->mapResize(_pMapTool->getMapCountX(), _pMapTool->getMapCountY() + 1);
}

void MAPSCENE::callBackMapUp()
{
	_pMapTool->mapResize(_pMapTool->getMapCountX(), _pMapTool->getMapCountY() -1);
}

void MAPSCENE::callBackMapLeft()
{
	_pMapTool->mapResize(_pMapTool->getMapCountX()-1, _pMapTool->getMapCountY() );
}

void MAPSCENE::callBackMapRight()
{
	_pMapTool->mapResize(_pMapTool->getMapCountX()+1, _pMapTool->getMapCountY() );
}

void MAPSCENE::callBackMapSave()
{
	_pMapTool->save();
}

void MAPSCENE::callBackMapLoad()
{
	_pMapTool->load();
}

void MAPSCENE::callBackGotoGameScene()
{
	SCENEMANAGER->changeScene("playGame");
	_endScene = true;
}
