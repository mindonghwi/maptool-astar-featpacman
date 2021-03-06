#pragma once
#include "stdafx.h"

//0 이면 벽
//139 이면 길

enum {PASS = 139};

class TILE 
{
public:
	enum OBJECT
	{
		NONE = 0,
		PACMAN,
		ENEMY01,
		ENEMY02,
		ENEMY03,
		ENEMY04,
		ITEM,
		MAX
	};

	enum class TERRIAN
	{
		NONE = 0,
		WALL,
		PASS,
		MAX
	};


public:
	TILE();
	~TILE();

private:
	int		_nAroundWall;		//주변벽값을 가진다.
	
	bool	_bIsWall;			//벽인지 아닌지 아직 2개 밖에 없어서 가능한 방식 나중에는 바꾸어야한다 테리안으로
	TILE::TERRIAN	_terrian;	//2가지가 아니라면 terrian을 사용해서 찾아야 한다.
	
	image*	_pImage;			//이미지를 담을 것이다.
	int		_nFrameX;			//프레임 넘버 X
	int		_nFrameY;			//프레임 넘버 Y
	RECT	_rcTile;			//사각형
	int		_nNodeIndex;		//몇번째 노드인지 넣는 함수
	OBJECT	_object;			//무슨 오브젝트가 있는지
	image*	_pObjectImage;		//오브젝트 이미지 none이면 아무것도 안그림

	RECT	_rcCameraLimit;

public:
	void	setttingObject();
	
public:
	//초기 초기화
	void	init(int nTileLeft, int nTileTop, int nTileSize,image* pImg,int nNodeIndex);
	
	//그려주는 함수
	void	render(HDC hdc);

	//메모리 해제
	void	release();

	//타일 세팅
	void	settingTile(int nFrameX, int nFrameY, bool bIsWall,OBJECT object);
	
	//타일 세팅이 끝나면 재조정한 것을 받아온다 클릭을 멈추는 순간에 업데이트를 한번에 해서 받아온다.
	void	readjustWall(int nAroundWall, int nFrameX, int nFrameY);

	string	makeSaveString();

	bool	setObject(OBJECT object);
	OBJECT	getObject();

	void	move(int vertical,int horizontal);

public:
	//setter
	inline	void	setAroundWall(int nAroundWall) { _nAroundWall = nAroundWall; }
	inline	void	setIsWall(bool isWall) { _bIsWall = isWall; }
	inline	void	setImg(image* pImg) { _pImage = pImg; }
	inline	void	setFrameX(int nFrameX) { _nFrameX = nFrameX; }
	inline	void	setFrameY(int nFrameY) { _nFrameY = nFrameY; }
	inline	void	setRectTile(RECT& rcTile) {	_rcTile = rcTile;}
	inline	void	setRectTile(int nLeft, int nTop, int nWidth, int nHeight) { _rcTile = RectMake(nLeft, nTop, nWidth, nHeight); }
	inline	void	setNodeIndex(int nIndex) { _nNodeIndex = nIndex; }
	inline	void	setLimitRect(RECT rc) { _rcCameraLimit = rc; }
	inline	void	setTerrian(TILE::TERRIAN terrian) { _terrian = terrian; }


	//getter
	inline	int				getAroundWall() { return _nAroundWall; }
	inline	bool			getIsWall() { return _bIsWall; }
	inline	image*			getimg() { return _pImage; }
	inline	int				getFrameX() { return _nFrameX; }
	inline	int				setFrameY() { return _nFrameY; }
	inline	RECT			getRectTile() { return _rcTile; }
	inline	int				getNodeIndex() { return _nNodeIndex; }
	inline	TILE::TERRIAN	getTerrian() {return _terrian; }

};