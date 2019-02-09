#include "stdafx.h"
#include "pacMan.h"

PACMAN::PACMAN()
{
}

PACMAN::~PACMAN()
{
}

void PACMAN::init()
{
	_direction = PACMAN::PACMANDIRECTION::PACMAN_LEFT;
	
	_pImg = IMAGEMANAGER->findImage("pacman32");

	_speed = 70.0f;
	_fPosX = _pMapTool->getPacManPosX();
	_fPosY = _pMapTool->getPacManPosY();
	_nFrameX = 0;
	_nFrameY = 0;
	_fFrameCount = 0;
}

void PACMAN::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_direction = PACMAN::PACMANDIRECTION::PACMAN_LEFT;

	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_direction = PACMAN::PACMANDIRECTION::PACMAN_RIGHT;

	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_direction = PACMAN::PACMANDIRECTION::PACMAN_UP;

	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_direction = PACMAN::PACMANDIRECTION::PACMAN_DOWN;

	}
	move();


	_fFrameCount += TIMEMANAGER->getElapsedTime();
	if (_fFrameCount > 1)
	{
		if (_nFrameX == 0)
		{
			_nFrameX++;
		}
		else if (_nFrameX == 2)
		{
			_nFrameX++;
		}
		else if (_nFrameX == 1)
		{
			_nFrameX--;
		}
		else if (_nFrameX == 3)
		{
			_nFrameX--;
		}
		_fFrameCount = 0;
	}
}

void PACMAN::render(HDC hdc)
{
	_pImg->frameRender(hdc, _rc.left, _rc.top, _nFrameX,_nFrameY);

}

void PACMAN::release()
{
	_pImg = nullptr;
	_pMapTool = nullptr;
}

void PACMAN::move()
{
	//가상의 충돌판정 렉트임
	RECT rcCollision;

	int tileIndex[2][2];	//이동 방향에 따라 타일속성을 검출하기 위한 타일 인덱스 값 계산용
	int tileX, tileY;	//실제 탱크가 어디 타일에 있는지 검출용

						//탱크가 있는 인덱스
	int tankTileIndex(0);
	//비교위한 렉
	RECT rcTmp;
	//비교할 렉트 2개
	RECT arRectCollision[2];
	//백하냐 안하냐
	bool isMoveWall = false;
	float tmpX = _fPosX ;
	float tmpY = _fPosY ;

	// 가상의 충돌판정 렉트에 탱크 렉트를 대입을 한다.
	rcCollision = _rc;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elapsedTime * _speed;
	//Unity -> deltaTime


	switch (_direction)
	{
	case PACMANDIRECTION::PACMAN_LEFT:
		if (_nFrameX == 2)
		{
			_nFrameX = 0;
		}
		if (_nFrameX == 3)
		{
			_nFrameX = 1;
		}
		_nFrameY = 1;

		_fPosX -= moveSpeed;
		break;
	case PACMANDIRECTION::PACMAN_UP:
		if (_nFrameX == 0)
		{
			_nFrameX = 2;
		}
		if (_nFrameX == 1)
		{
			_nFrameX = 3;
		}
		_nFrameY = 1;

		_fPosY -= moveSpeed;
		break;
	case PACMANDIRECTION::PACMAN_RIGHT:
		if (_nFrameX == 2)
		{
			_nFrameX = 0;
		}
		if (_nFrameX == 3)
		{
			_nFrameX = 1;
		}
		_nFrameY = 0;


		_fPosX += moveSpeed;
		break;
	case PACMANDIRECTION::PACMAN_DOWN:
		if (_nFrameX == 0)
		{
			_nFrameX = 2;
		}
		if (_nFrameX == 1)
		{
			_nFrameX = 3;
		}
		_nFrameY = 0;

		_fPosY += moveSpeed;
		break;

	}


	//팁 번외편.
	//가상의 충돌렉트를 살짝 깍아둔다면?! 28x28
	rcCollision = RectMakeCenter(_fPosX, _fPosY, _pImg->getFrameWidth() - 8, _pImg->getFrameHeight() - 8);


	//팁3 밑에껄 연산해둔다 
	//tileX = 전체타일 나누기 rcCollision의 left
	tileX = (_fPosX - _pMapTool->getTileSize() / 2) * 20 / 640;
	tileY = (_fPosY - _pMapTool->getTileSize() / 2) * 20 / 640;



	//팁4 여기를 계산한다. 연습장 필요할듯
	switch (_direction)
	{
	case PACMANDIRECTION::PACMAN_LEFT:
		//맵 밖으로 나가는 것 방지
		if (_fPosX <  _pImg->getFrameWidth()/2)
		{
			isMoveWall = true;
		}
		else {
			//안나갔을때
			tileIndex[0][0] = tileX;
			tileIndex[0][1] = tileY;

			tileIndex[1][0] = tileX;
			tileIndex[1][1] = tileY + 1;
		}

		break;
	case PACMANDIRECTION::PACMAN_UP:

		if (_fPosY <  _pImg->getFrameHeight() / 2)
		{
			isMoveWall = true;
		}
		else
		{
			tileIndex[0][0] = tileX;
			tileIndex[0][1] = tileY;

			tileIndex[1][0] = tileX + 1;
			tileIndex[1][1] = tileY;
		}

		break;
	case PACMANDIRECTION::PACMAN_RIGHT:

		if (_fPosX > _pMapTool->getMapCountX() * _pMapTool->getTileSize() - _pMapTool->getTileSize()/2)
		{
			isMoveWall = true;
		}
		else {

			tileIndex[0][0] = tileX + 1;
			tileIndex[0][1] = tileY;

			tileIndex[1][0] = tileX + 1;
			tileIndex[1][1] = tileY + 1;

		}

		break;
	case PACMANDIRECTION::PACMAN_DOWN:

		if (_fPosY > _pMapTool->getMapCountY() * _pMapTool->getTileSize() - _pMapTool->getTileSize() / 2)
		{
			isMoveWall = true;
		}
		else
		{
			tileIndex[0][0] = tileX;
			tileIndex[0][1] = tileY + 1;

			tileIndex[1][0] = tileX + 1;
			tileIndex[1][1] = tileY + 1;

		}
		break;

	}

	if (!isMoveWall)
	{
		for (int i = 0; i < 2; i++)
		{
			arRectCollision[i] = _pMapTool->getTile(tileIndex[i][0], tileIndex[i][1])->getRectTile();

			if (IntersectRect(&rcTmp, &rcCollision, &arRectCollision[i]))
			{
				if (_pMapTool->getTile(tileIndex[i][0], tileIndex[i][1])->getIsWall())
				{
					isMoveWall = true;
					break;
				}
			}
		}
	}

	if (isMoveWall)
	{
		_fPosX = tmpX;
		_fPosY = tmpY;
	}
	
	switch (_direction)
	{
	case PACMAN::PACMANDIRECTION::PACMAN_LEFT:
		if (!isMoveWall)
		_pCamera->moveLeft(moveSpeed);
		break;
	case PACMAN::PACMANDIRECTION::PACMAN_UP:
		if (!isMoveWall)
		_pCamera->moveUp(moveSpeed);
		break;
	case PACMAN::PACMANDIRECTION::PACMAN_RIGHT:
		if (!isMoveWall)
		_pCamera->moveRight(moveSpeed);
		break;
	case PACMAN::PACMANDIRECTION::PACMAN_DOWN:
		if (!isMoveWall)
		_pCamera->moveDown(moveSpeed);
		break;
	}
	_rc = RectMakeCenter(_fPosX, _fPosY, _pImg->getFrameWidth(), _pImg->getFrameHeight());
}
