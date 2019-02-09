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
	list<TILENODE*>			_listSearchedNode;	//Ž���� ������ ��� list
	stack<TILENODE*>		_stackPriorityPath;	//�켱�������� ��� ����Ʈ
	list<TILENODE*>			_listMaximumPath;	//end���� ���۵Ǵ� �ִܰ�ΰ� ��� ����Ʈ
	vector<int> _vX;
	vector<int> _vY;
	//						  ��		  ��			��		��		�»�    ���   ����     ����
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
	void	pathFinder(int nCurrentIndexX, int nCurrentIndexY);	// _stackPriority���� �ϼ��� �ȴ�.
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


