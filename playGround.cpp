#include "stdafx.h"
#include "playGround.h"
#include"mapCreateScene.h"
#include "gameScene.h"
playGround::playGround()
{
}


playGround::~playGround()
{
}



HRESULT playGround::init()
{
	gameNode::init(true);


	_pMapScene = new MAPSCENE;
	_pPlayScene = new GAMESCENE;

	SCENEMANAGER->addScene("MapTool", _pMapScene);
	SCENEMANAGER->addScene("playGame", _pPlayScene);

	SCENEMANAGER->changeScene("MapTool");

	return S_OK;
}


void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown('K'))
	{

	}


	SCENEMANAGER->update();

}



void playGround::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	SCENEMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	//===========================================================
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
