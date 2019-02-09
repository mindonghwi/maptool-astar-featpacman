#include "stdafx.h"
#include "camera.h"

CAMERA::CAMERA()
{
}

CAMERA::~CAMERA()
{
}

void CAMERA::init(int posX, int posY, int width, int height)
{
	_posX = posX;
	_posY = posY;
	_width = width;
	_height = height;
	setLeftTop();

	_rcCameraLimit = { 0,0,CAMERASIZEX,CAMERASIZEY };

	_pCameraBuffer = IMAGEMANAGER->addImage("camera", CAMERASIZEX,CAMERASIZEY);
}

void CAMERA::update()
{
	moveToPlayer();
}

void CAMERA::render(HDC hdc)
{
	_pCameraBuffer->render(hdc, 0, 0, _left, _top, _width, _height);
}

void CAMERA::renderinit()
{
	PatBlt(_pCameraBuffer->getMemDC(), 0, 0, CAMERASIZEX, CAMERASIZEY, WHITENESS);

	//_pBac->render(_pCameraBuffer->getMemDC(), 0, 0);
}

void CAMERA::setting(int nPosX, int nPosY)
{
	_posX = nPosX;
	_posY = nPosY;
	outOfRange();
	setLeftTop();
}

void CAMERA::setMap(image * background)
{
	//_pBac = background;
}

void CAMERA::settingCameraRange(int nLeft, int nTop, int nRight, int nBottom)
{
	_rcCameraLimit = { nLeft,nTop,nRight,nBottom };
}

void CAMERA::setLeftTop()
{
	_left = _posX - _width / 2;
	_top = _posY - _height / 2;
}

void CAMERA::moveRight(float offset)
{
	_posX += offset;
	if (_posX + _width / 2 >= _rcCameraLimit.right)
	{
		_posX = _rcCameraLimit.right - _width / 2;
	}
	setLeftTop();

}

void CAMERA::moveLeft(float offset)
{
	_posX -= offset;
	if (_posX - _width / 2 <= 0)
	{
		_posX = _width / 2;
	}
	setLeftTop();

}

void CAMERA::moveUp(float offset)
{
	_posY -= offset;
	if (_posY - _height / 2 <= 0)
	{
		_posY = _height / 2;
	}
	setLeftTop();

}

void CAMERA::moveDown(float offset)
{
	_posY += offset;

	if (_posY + _height / 2 >= _rcCameraLimit.bottom)
	{
		_posY = _rcCameraLimit.bottom - _height / 2;
	}
	setLeftTop();
}

void CAMERA::moveToPlayer()
{
	//if (!_isMoving) return;


	//if (_pPlayer->getPosX() > _posX) {
	//	float moveSpeed = (TIMEMANAGER->getElpasedTime()) * _travelRangeX;
	//	moveRight(moveSpeed);

	//}
	//else
	//{
	//	float moveSpeed = (TIMEMANAGER->getElpasedTime()) * _travelRangeX;
	//	moveLeft(moveSpeed);

	//}

	//if (_pPlayer->getPosY() > _posY) {
	//	float moveSpeed = (TIMEMANAGER->getElpasedTime()) * _travelRangeY;
	//	moveDown(moveSpeed);
	//}
	//else
	//{
	//	float moveSpeed = (TIMEMANAGER->getElpasedTime()) * _travelRangeY;
	//	moveUp(moveSpeed);
	//}

	//_time += TIMEMANAGER->getElpasedTime();

	//if (_time > 1.0f)
	//{
	//	_isMoving = false;
	//}

}

void CAMERA::movingStart()
{
	//if (!_isMoving)
	//{
	//	_isMoving = true;
	//	_time = 0.0f;
	//}
	//
	//if (_pPlayer->getPosX() > _posX) {
	//	_travelRangeX = _pPlayer->getPosX() - _posX;
	//}
	//else
	//{
	//	_travelRangeX = _posX - _pPlayer->getPosX();
	//}

	//if (_pPlayer->getPosY() > _posY) {
	//	_travelRangeY = _pPlayer->getPosY() - _posY;
	//}
	//else
	//{
	//	_travelRangeY = _posY - _pPlayer->getPosY();
	//}

}

void CAMERA::outOfRange()
{
	if (_posX + _width / 2 >= _rcCameraLimit.right)
	{
		_posX = _rcCameraLimit.right - _width / 2;
	}
	else if (_posX - _width / 2 <= 0)
	{
		_posX = _width / 2;
	}

	if (_posY - _height / 2 <= 0)
	{
		_posY = _height / 2;
	}
	else if (_posY + _height / 2 >= _rcCameraLimit.bottom)
	{
		_posY = _rcCameraLimit.bottom - _height / 2;
	}
}
