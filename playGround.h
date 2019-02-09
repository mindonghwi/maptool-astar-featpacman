#pragma once
#include "gameNode.h"
#include "mapCreateScene.h"



class playGround : public gameNode
{
private:

	gameNode*	_pMapScene;
	gameNode*	_pPlayScene;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	playGround();
	~playGround();

private:
};

