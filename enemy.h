#pragma once

#include "stdafx.h"
#include "mapTool.h"
//#include "aStar.h"
//#include "astarAlgorithm.h"
#include "aStarSecond.h"

#include "pacMan.h"


class ENEMY
{
public:
	enum class ENEMYDIRECTION
	{
		ENEMY_LEFT,
		ENEMY_UP,
		ENEMY_RIGHT,
		ENEMY_DOWN
	};

	struct PATHNODE 
	{
		int	nIndexX;
		int nIndexY;
	};
public:
	ENEMY();
	~ENEMY();


	void init(TILE::OBJECT object, image* pImg);
	void update();
	void render(HDC hdc);
	void release();

private:
	image * _pImg;
	float	_fPosX;
	float	_fPosY;
	float _speed;
	RECT _rc;
	ENEMYDIRECTION _direction;
	MAPTOOL*		_pMapTool;
	ASTARTSECOND*	_pAStar;

	PACMAN*		_pPacMan;

	int		_nFrameX;
	int		_nFrameY;


	float	_fFrameCount;
	float	_fSearchCount;

	int		_nMovingPointX;
	int		_nMovingPointY;

	float	_travelRangeX;
	float	_travelRangeY;

	vector<PATHNODE*> _vPath;
	int				_nPathIndex;

	TILE::OBJECT	_obj;
private:
	void move();
	void moveStart();
public:
	void setMapTool(MAPTOOL* pMapTool) { _pMapTool = pMapTool; }
	void setPacMan(PACMAN* pPacman) { _pPacMan = pPacman; }

	inline	float	getPosX() { return _fPosX; }
	inline	float	getPosY() { return _fPosY; }
	inline	void	setPosX(float fPosX) { _fPosX = fPosX; }
	inline	void	setPosY(float fPosY) { _fPosY = fPosY; }
};
