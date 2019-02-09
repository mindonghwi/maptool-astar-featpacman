#include "stdafx.h"
#include "enemy.h"

ENEMY::ENEMY()
{
}

ENEMY::~ENEMY()
{
}

void ENEMY::init(TILE::OBJECT object, image* pImg)
{
	_direction = ENEMY::ENEMYDIRECTION::ENEMY_UP;

	_pImg = pImg;

	_speed = 70.0f;
	int	nPosX = 0;
	int nPosY = 0;
	_obj = object;
	_pMapTool->getEnemyPos(&nPosX, &nPosY, object);

	_fPosX = _pMapTool->getEnemyPosX(_obj);
	_fPosY = _pMapTool->getEnemyPosY(_obj);
	_nFrameX = 0;
	_nFrameY = 0;
	_fFrameCount = 0;
	_nPathIndex = 0;

	_pAStar = new ASTARTSECOND();
	_pAStar->init(4);
	_pAStar->setMapTool(_pMapTool);
	_pAStar->setObject(_obj);

	nPosX = _pPacMan->getPosX();
	nPosY = _pPacMan->getPosY();

	_pAStar->startFinder(_fPosX / _pMapTool->getTileSize(), _fPosY / _pMapTool->getTileSize(),
		_pPacMan->getPosX() / _pMapTool->getTileSize(), _pPacMan->getPosY() / _pMapTool->getTileSize());
	_pAStar->pathFinder();


	for (int i = 0; i < _pAStar->getListSize(); i++)
	{
		_vPath.push_back(new PATHNODE);
		_vPath.back()->nIndexX = _pAStar->getNode(i)->nIndexX;
		_vPath.back()->nIndexY = _pAStar->getNode(i)->nIndexY;
	}



	moveStart();

	_fSearchCount = 0;

}

void ENEMY::update()
{
	//�̵�ó���� �ٲٸ� �ȴ�.

	_fSearchCount += TIMEMANAGER->getElapsedTime();
	//if (_fSearchCount >= 10.0f)
	{
		

		_fSearchCount = 0;
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

void ENEMY::render(HDC hdc)
{
	_pImg->frameRender(hdc, _rc.left, _rc.top, _nFrameX, _nFrameY);

}

void ENEMY::release()
{
	_pImg = nullptr;
	_pMapTool = nullptr;
	_pAStar->release();
	delete _pAStar;
	_pAStar = nullptr;
}

void ENEMY::move()
{
	//������ �浹���� ��Ʈ��
	RECT rcCollision;

	int tileIndex[2][2];	//�̵� ���⿡ ���� Ÿ�ϼӼ��� �����ϱ� ���� Ÿ�� �ε��� �� ����
	int tileX, tileY;	//���� ��ũ�� ��� Ÿ�Ͽ� �ִ��� �����

						//��ũ�� �ִ� �ε���
	int tankTileIndex(0);
	//������ ��
	//���� ��Ʈ 2��
	RECT arRectCollision[2];
	//���ϳ� ���ϳ�
	bool isMoveWall = false;
	float tmpX = _fPosX;
	float tmpY = _fPosY;

	// ������ �浹���� ��Ʈ�� ��ũ ��Ʈ�� ������ �Ѵ�.
	rcCollision = _rc;

	float elapsedTime = TIMEMANAGER->getElapsedTime();
	//float moveSpeed = elapsedTime * _speed;
	//Unity -> deltaTime
	bool	isWall[4]{};


	

	float moveSpeedX = _travelRangeX;//*(TIMEMANAGER->getElapsedTime()); 
	float moveSpeedY = _travelRangeY;//*(TIMEMANAGER->getElapsedTime()); 

	RECT rcTmp;
	if (IntersectRect(&rcTmp, &rcCollision, &RectMakeCenter(_pPacMan->getPosX(), _pPacMan->getPosY(), 32, 32)))
	{
		return;
	}



	switch (_direction)
	{
	case ENEMYDIRECTION::ENEMY_LEFT:
		if (_nFrameX == 2)
		{
			_nFrameX = 0;
		}
		if (_nFrameX == 3)
		{
			_nFrameX = 1;
		}
		_nFrameY = 1;

		_fPosX -= moveSpeedX;
		break;
	case ENEMYDIRECTION::ENEMY_UP:
		if (_nFrameX == 0)
		{
			_nFrameX = 2;
		}
		if (_nFrameX == 1)
		{
			_nFrameX = 3;
		}
		_nFrameY = 1;

		_fPosY -= moveSpeedY;
		break;
	case ENEMYDIRECTION::ENEMY_RIGHT:
		if (_nFrameX == 2)
		{
			_nFrameX = 0;
		}
		if (_nFrameX == 3)
		{
			_nFrameX = 1;
		}
		_nFrameY = 0;


		_fPosX += moveSpeedX;
		break;
	case ENEMYDIRECTION::ENEMY_DOWN:
		if (_nFrameX == 0)
		{
			_nFrameX = 2;
		}
		if (_nFrameX == 1)
		{
			_nFrameX = 3;
		}
		_nFrameY = 0;

		_fPosY += moveSpeedY;
		break;

	}



	//�� ������.
	//������ �浹��Ʈ�� ��¦ ��Ƶдٸ�?! 28x28
	rcCollision = RectMakeCenter(_fPosX, _fPosY, _pImg->getFrameWidth()-2 , _pImg->getFrameHeight() - 2);
	if (IntersectRect(&rcTmp, &_pMapTool->getTile(_vPath[_nPathIndex]->nIndexX, _vPath[_nPathIndex]->nIndexY)->getRectTile(), &rcCollision))
	{
		if (rcTmp.left == rcCollision.left&&
			rcTmp.top == rcCollision.top&&
			rcTmp.right == rcCollision.right&&
			rcTmp.bottom == rcCollision.bottom)
		{

			_nPathIndex++;
			moveStart();
		}
	}

	

	//��3 �ؿ��� �����صд� 
	//tileX = ��üŸ�� ������ rcCollision�� left
	
	_rc = RectMakeCenter(_fPosX, _fPosY, _pImg->getFrameWidth(), _pImg->getFrameHeight());
}

void ENEMY::moveStart()
{
	if (_nPathIndex >= _pAStar->getListSize())
	{
		_pMapTool->deleteObject();

		_pAStar->startFinder(_fPosX / _pMapTool->getTileSize(), _fPosY / _pMapTool->getTileSize(),
			_pPacMan->getPosX() / _pMapTool->getTileSize(), _pPacMan->getPosY() / _pMapTool->getTileSize());
		_pAStar->pathFinder();

		for (int i = 0; i < _pAStar->getListSize(); i++)
		{
			if (i < _vPath.size())
			{
				_vPath[i]->nIndexX = _pAStar->getNode(i)->nIndexX;
				_vPath[i]->nIndexY = _pAStar->getNode(i)->nIndexY;
			}
			else {
				_vPath.push_back(new PATHNODE);
				_vPath.back()->nIndexX = _pAStar->getNode(i)->nIndexX;
				_vPath.back()->nIndexY = _pAStar->getNode(i)->nIndexY;
			}
		}
		_nPathIndex = 0;

	}


	_nMovingPointX = _vPath[_nPathIndex]->nIndexX;
	_nMovingPointY = _vPath[_nPathIndex]->nIndexY;

	int tileX = (_fPosX ) * 20 / 640;
	int tileY = (_fPosY ) * 20 / 640;

	if (_nMovingPointX > tileX) {
		_travelRangeX = _nMovingPointX - tileX;
		_direction = ENEMYDIRECTION::ENEMY_RIGHT;
	}
	else if(_nMovingPointX < tileX)
	{
		_travelRangeX = tileX - _nMovingPointX;
		_direction = ENEMYDIRECTION::ENEMY_LEFT;
	}
	else if (_nMovingPointY > tileY) {
		_travelRangeY = _nMovingPointY - tileY;
		_direction = ENEMYDIRECTION::ENEMY_DOWN;
	}
	else if (_nMovingPointY < tileY)
	{
		_travelRangeY = tileY - _nMovingPointY;
		_direction = ENEMYDIRECTION::ENEMY_UP;
	}
}
