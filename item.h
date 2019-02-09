#pragma once
#include "stdafx.h"


class ITEM
{
public:
	ITEM();
	~ITEM();

private:
	int		_nPoint;
	int		_nPosLeft;
	int		_nPosTop;
	int		_nWidth;
	int		_nHeight;
	RECT	_rcItem;
	image*	_pImg;
public:
	void init(int nPosLeft, int nPosTop, image*	pImg);
	void release();
	void render(HDC hdc, int nCluppingLeft, int nCluppingRight, int nCluppingTop, int nCluppingBottom);
	int	getPoint() { return _nPoint; }
	LPCRECT	getRect() { return &_rcItem; }
};
