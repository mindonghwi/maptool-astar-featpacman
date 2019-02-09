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
	list<TILENODE*>			_listOpendNode;		//Ž���� �Ҽ� �ִ� ������ ����.
	list<TILENODE*>			_listClosedyPath;	//Ž���� ���� ������ ����.
	list<TILENODE*>			_listMaximumPath;	//������ ��ε��� ��� ����Ʈ

	//						  ��		  ��			��		��		�»�    ���   ����     ����
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
	int				_nSearchLength;//4�� 8
public:
	ASTARTSECOND();
	~ASTARTSECOND();
	void	init(int nSearchLength);
	//��� Ÿ�Ͽ� �ִ��� �ִ� �Լ�
	void	startFinder(int nStartIndexX, int nStartIndexY, int nEndIndexX, int nEndIndexY);
	void	pathFinder();	// _stackPriority���� �ϼ��� �ȴ�.

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