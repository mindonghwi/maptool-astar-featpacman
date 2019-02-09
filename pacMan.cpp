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
	//������ �浹���� ��Ʈ��
	RECT rcCollision;

	int tileIndex[2][2];	//�̵� ���⿡ ���� Ÿ�ϼӼ��� �����ϱ� ���� Ÿ�� �ε��� �� ����
	int tileX, tileY;	//���� ��ũ�� ��� Ÿ�Ͽ� �ִ��� �����

						//��ũ�� �ִ� �ε���
	int tankTileIndex(0);
	//������ ��
	RECT rcTmp;
	//���� ��Ʈ 2��
	RECT arRectCollision[2];
	//���ϳ� ���ϳ�
	bool isMoveWall = false;
	float tmpX = _fPosX ;
	float tmpY = _fPosY ;

	// ������ �浹���� ��Ʈ�� ��ũ ��Ʈ�� ������ �Ѵ�.
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


	//�� ������.
	//������ �浹��Ʈ�� ��¦ ��Ƶдٸ�?! 28x28
	rcCollision = RectMakeCenter(_fPosX, _fPosY, _pImg->getFrameWidth() - 8, _pImg->getFrameHeight() - 8);


	//��3 �ؿ��� �����صд� 
	//tileX = ��üŸ�� ������ rcCollision�� left
	tileX = (_fPosX - _pMapTool->getTileSize() / 2) * 20 / 640;
	tileY = (_fPosY - _pMapTool->getTileSize() / 2) * 20 / 640;



	//��4 ���⸦ ����Ѵ�. ������ �ʿ��ҵ�
	switch (_direction)
	{
	case PACMANDIRECTION::PACMAN_LEFT:
		//�� ������ ������ �� ����
		if (_fPosX <  _pImg->getFrameWidth()/2)
		{
			isMoveWall = true;
		}
		else {
			//�ȳ�������
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
