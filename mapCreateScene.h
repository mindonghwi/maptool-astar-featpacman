#pragma once

#include "stdafx.h"
#include "gameNode.h"
#include "mapTool.h"
#include "button.h"
#include "camera.h"

class MAPSCENE :public gameNode
{
public:
	enum class BTN
	{
		MAPUP = 0,
		MAPDOWN,
		MAPLEFT,
		MAPRIGHT,
		MAX
	};

private:
	MAPTOOL*	_pMapTool;
	button*		_btn[static_cast<const int>(MAPSCENE::BTN::MAX)];
	button*		_btnSave;
	button*		_btnLoad;
	button*		_btnPlayGame;



	RECT		_rcWallPallet;
	RECT		_rcPassPallet;
	RECT		_arPallet[static_cast<const int>(TILE::OBJECT::MAX)];
	CAMERA*		_pCamera;
	
	bool		_endScene;

public:
	MAPSCENE();
	~MAPSCENE();


	virtual HRESULT init()	override;
	virtual void release()	override;
	virtual void update()	override;
	virtual void render()	override;

private:
	void	setup();



public:
	void	callBackMapDown();
	void	callBackMapUp();
	void	callBackMapLeft();
	void	callBackMapRight();
	void	callBackMapSave();
	void	callBackMapLoad();
	void	callBackGotoGameScene();
};