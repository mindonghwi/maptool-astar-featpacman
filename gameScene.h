#pragma once

#include "mapTool.h"
#include "stdafx.h"
#include "gameNode.h"
#include "camera.h"
#include "pacMan.h"
#include "enemy.h"
#include "itemMgr.h"

class GAMESCENE : public gameNode
{
public:
	GAMESCENE();
	~GAMESCENE();
	
	virtual HRESULT init()	override;
	virtual void release()	override;
	virtual void update()	override;
	virtual void render()	override;

private:
	MAPTOOL*	_pMapTool;
	CAMERA*		_pCamera;
	PACMAN*		_pPacMan;
	ENEMY*		_pEnemy[4];
	ITEMMGR*	_pItemMgr;
private:
	void setWindowsSize(int x, int y, int width, int height);
};
