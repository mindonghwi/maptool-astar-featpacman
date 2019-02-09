#include "stdafx.h"
#include "item.h"

ITEM::ITEM()
{
}

ITEM::~ITEM()
{
}

void ITEM::init(int nPosLeft, int nPosTop, image*	pImg)
{
	_nPosLeft = nPosLeft;
	_nPosTop = nPosTop;
	_pImg = pImg;
	_nWidth = _pImg->getFrameWidth();
	_nHeight = _pImg->getFrameHeight();
	_rcItem = RectMake(_nPosLeft, _nPosTop, _nWidth, _nHeight);
	
	_rcItem.left += 5;
	_rcItem.right -= 5;
	_rcItem.top += 5;
	_rcItem.bottom -= 5;

	_nPoint = 10;
}

void ITEM::release()
{
	_pImg = nullptr;
}

void ITEM::render(HDC hdc, int nCluppingLeft, int nCluppingRight, int nCluppingTop, int nCluppingBottom)
{
	if (_rcItem.right	> nCluppingLeft		&&
		_rcItem.left	< nCluppingRight	&&
		_rcItem.bottom	> nCluppingTop		&&
		_rcItem.top		< nCluppingBottom	)
	{
		_pImg->frameRender(hdc, _nPosLeft, _nPosTop, 0, 0);
	}
}
