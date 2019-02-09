#pragma once

#include "stdafx.h"
#include "mapTool.h"


class ASTARTSECOND {

public:
	struct TILENODE
	{
		int			nIndexX;
		int			nIndexY;
		int			nPathStartToCurrent;
		int			nPathCurrentToEnd;
		int			nPathToatalCost;
		TILENODE*	parrentNode;
	};

	enum POS
	{
		POSX = 0,
		POSY,
		MAX
	};

private:
	list<TILENODE*>			_listOpendNode;		//탐색을 할수 있는 노드들이 담긴다.
	list<TILENODE*>			_listClosedyPath;	//탐색이 끝난 노드들이 담긴다.
	list<TILENODE*>			_listMaximumPath;	//마지막 경로들이 담길 리스트

	//						  상		  하			좌		우		좌상    우상   좌하     우하
	int	_arInterval[8][2]{ { 0,-1 },{ 0,1 },{ -1,0 },{ 1,0 },{ -1,-1 },{ 1,-1 },{ -1,1 },{ 1,1 } };
	int	_arHuristic[8]{		  10,	  10,		10,		10,		14,			14,		14,		14 };

	MAPTOOL*		_pMapTool;
	int				_nTileSizeX;
	int				_nTileSizeY;

	int				_nStartIndexX;
	int				_nStartIndexY;
	int				_nEndIndexX;
	int				_nEndIndexY;

	TILE::OBJECT	_obj;
	int				_nSearchLength;//4나 8
public:
	ASTARTSECOND();
	~ASTARTSECOND();
	void	init(int nSearchLength);
	//어느 타일에 있는지 주는 함수
	void	startFinder(int nStartIndexX, int nStartIndexY, int nEndIndexX, int nEndIndexY);
	void	pathFinder();	// _stackPriority까지 완성이 된다.

	void	setMapTool(MAPTOOL* pMapTool);
	void	setObject(TILE::OBJECT obj);
	void	release();
	TILENODE*	getTileNode();
	void	getNextTile(int* nX, int *nY);


	list<TILENODE*>&		getPath() { return _listMaximumPath; }
	int		getListSize() { return _listMaximumPath.size(); }
	TILENODE*	getNode(int nIndex);
	bool	bIsEmety() { return _listMaximumPath.empty(); }


};