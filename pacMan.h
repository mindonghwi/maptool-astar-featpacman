#pragma once

#include "stdafx.h"
#include "mapTool.h"

class CAMERA;

class PACMAN
{
public:
	enum class PACMANDIRECTION
	{
		PACMAN_LEFT,
		PACMAN_UP,
		PACMAN_RIGHT,
		PACMAN_DOWN
	};
public:
	PACMAN();
	~PACMAN();


	void init();
	void update();
	void render(HDC hdc);
	void release();

private:
	image * _pImg;
	float	_fPosX;
	float	_fPosY;
	float _speed;
	RECT _rc;
	PACMANDIRECTION _direction;
	MAPTOOL*		_pMapTool;
	CAMERA*			_pCamera;


	int		_nFrameX;
	int		_nFrameY;


	float	_fFrameCount;
private:
	void move();

public:
	void setMapTool(MAPTOOL* pMapTool) { _pMapTool = pMapTool; }
	void setCamera(CAMERA* pCamera) { _pCamera = pCamera; }


	inline	float	getPosX() { return _fPosX; }
	inline	float	getPosY() { return _fPosY; }
	inline	void	setPosX(float fPosX) { _fPosX = fPosX; }
	inline	void	setPosY(float fPosY) { _fPosY = fPosY; }
};
