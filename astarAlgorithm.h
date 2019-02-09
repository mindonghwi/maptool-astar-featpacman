#pragma once

#include "stdafx.h"
#include "mapTool.h"
class MAPTOOL;




class ASTAR_ALGORITHM
{
public:
	struct TILENODE
	{
		int		nIndexX;
		int		nIndexY;
		int		nPathCost;
	};

	enum POS
	{
		POSX = 0,
		POSY,
		MAX
	};
private:
	list<TILENODE*>			_listSearchedNode;	//탐색된 노드들이 담긴 list
	stack<TILENODE*>		_stackPriorityPath;	//우선순위들이 담길 리스트
	list<TILENODE*>			_listMaximumPath;	//end부터 시작되는 최단경로가 담길 리스트
	vector<int> _vX;
	vector<int> _vY;
	//						  상		  하			좌		우		좌상    우상   좌하     우하
	int	_arInterval[8][2]{ { 0,-1 },{ 0,1 },{ -1,0 },{ 1,0 },{ -1,-1 },{ 1,-1 },{ -1,1 },{ 1,1 } };
	int	_arHuristic[8]{ 10,	  10,		10,		10,		14,		14,			14,		14 };

	MAPTOOL*		_pMapTool;
	int				_nTileSizeX;
	int				_nTileSizeY;

	int				_nStartPosX;
	int				_nStartPosY;
	int				_nEndIndexX;
	int				_nEndIndexY;



	TILE::OBJECT	_obj;
public:
	ASTAR_ALGORITHM();
	~ASTAR_ALGORITHM();

	void	init();
	void	startFinder(int nStartIndexX, int nStartIndexY, int nEndIndexX, int nEndIndexY);
	void	pathFinder(int nCurrentIndexX, int nCurrentIndexY);	// _stackPriority까지 완성이 된다.
	void	makePath();
	void	makeFailPath();

	void	setMapTool(MAPTOOL* pMapTool);
	void	setObject(TILE::OBJECT obj);
	void	release();

	list<TILENODE*>&		getPath() { return _listMaximumPath; }


	TILENODE*	getTileNode();

	void	getNextTile(int* nX, int *nY);

	bool	bIsEmety() { return _listMaximumPath.empty(); }
};


