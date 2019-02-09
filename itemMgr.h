#pragma once
#include "stdafx.h"
#include "item.h"
#include "mapTool.h"
#include "tile.h"
#include "pacMan.h"

class ITEMMGR
{
public:
	ITEMMGR();
	~ITEMMGR();

private:
	MAPTOOL*		_pMapTool;
	CAMERA*			_pCamera;
	PACMAN*			_pPacman;
	vector<ITEM*>	_vItem;

public:
	void	init();
	void	update();
	void	release();
	void	render();


	void setPacMan(PACMAN* pPacman) { _pPacman = pPacman; }
	void setMapTool(MAPTOOL* pMapTool) { _pMapTool = pMapTool; }
	void setCamera(CAMERA* pCamera) { _pCamera = pCamera; }
};