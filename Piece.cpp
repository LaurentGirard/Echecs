/**
* @file Piece.cpp
* @author P. Sullivan, G.Laurent
* @since 25/12/2015
* @brief implémentation des méthodes de la classe Piece
*
**/

#include "Piece.hpp"

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS PIECE ------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

Piece::Piece(unsigned int x, unsigned int y) : alive(true), label(" ")
{
	square = new Cell(x,y);
}

//------------------------------------------------------------------------------------------------------
Piece::~Piece(){}

//------------------------------------------------------------------------------------------------------
Cell* Piece::getSquare()
{
	return square;
}

//------------------------------------------------------------------------------------------------------
void Piece::setSquare(Cell* newCell)
{
	square->setX(newCell->getX());
	square->setY(newCell->getY());
}

//------------------------------------------------------------------------------------------------------
bool Piece::asAlive()
{
	return alive;
}

//------------------------------------------------------------------------------------------------------
void Piece::setAlive(bool newAlive)
{
	alive = newAlive;
}
//------------------------------------------------------------------------------------------------------
std::string Piece::getLabel()
{
	return label;
}

//------------------------------------------------------------------------------------------------------
void Piece::printPiece()
{
	std::cout << "X position : " << square->getX() << std::endl;
	std::cout << "Y position : " << square->getY() << std::endl;
}
//------------------------------------------------------------------------------------------------------
void Piece::movement() {}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS SPAWN -------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

Spawn::Spawn(unsigned int x, unsigned int y) : Piece(x,y)
{
	label = "S";
	/*std::cout << "Buggg  ici ???? "<< std::endl;
	movements[0].push_back(Cell(x,y+1));
	std::cout << "Oui ???"<< std::endl;
	movements[0].push_back(Cell(x,y+2));*/

}

//------------------------------------------------------------------------------------------------------
Spawn::~Spawn(){}

//------------------------------------------------------------------------------------------------------
void Spawn::movement()
{	/*
	movements.clear();
	if(square->getY()<7)
		movements[0].push_back(Cell(square->getX(),square->getY()+1));
*/
}


//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS ROOK -------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

Rook::Rook(unsigned int x, unsigned int y) : Piece(x,y), _moved(0)
{
	label = "R";
	/*
	int i;
	for(i = 1; i < 8 ; ++i)
	{
		movements[0].push_back(Cell(x,i));
	};
	if (x==0)
	{
		for(i = 1; i < 8 ; ++i)
		{
			movements[1].push_back(Cell(i,0));
		};
	}else
	{
		for(i = 1; i < 8 ; ++i)
		{
			movements[1].push_back(Cell(x-i,0));
		};
	}*/
}

//------------------------------------------------------------------------------------------------------
Rook::~Rook(){}

//------------------------------------------------------------------------------------------------------
bool Rook::asMoved()
{
	return _moved;
}

//------------------------------------------------------------------------------------------------------
void Rook::setMoved(bool newMoved)
{
	_moved = newMoved;
}

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void Rook::movement()
{/*
	movements.clear();
	int x=square->getX();
	int y=square->getY();
	int i;
	for (i=1; x+i < 8 ; ++i)
	{
		movements[0].push_back(Cell(x+i,y));
	} 
	for (i=1; x-i > -1 ; ++i)
	{
		movements[1].push_back(Cell(x-i,y));
	}
	for (i=1; y+i < 8 ; ++i)
	{
		movements[0].push_back(Cell(x,y+i));
	} 
	for (i=1; y-i > -1 ; ++i)
	{
		movements[1].push_back(Cell(x,y-i));
	}*/
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS KNIGHT -----------------------------------------------------------
//------------------------------------------------------------------------------------------------------

Knight::Knight(unsigned int x, unsigned int y) : Piece(x,y)
{
	label = "C";
	/*
	if (x==1){
		movements[0].push_back(Cell(0,2));
		movements[1].push_back(Cell(2,2));
		movements[2].push_back(Cell(3,1));
	}else
	{
		movements[0].push_back(Cell(4,1));
		movements[1].push_back(Cell(5,2));
		movements[2].push_back(Cell(7,2));
	}*/
}

//------------------------------------------------------------------------------------------------------
Knight::~Knight(){}

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void Knight::movement()
{/*
	movements.clear();
	int x=square->getX();
	int y=square->getY();
	if(y+2<8)
	{
		if(x-1>-1) 	movements[0].push_back(Cell(x-1,y+2));
		if(x+1<8) 	movements[1].push_back(Cell(x+1,y+2));
	}
	if(x+2<8)
	{
		if(y+1<8) 	movements[2].push_back(Cell(x+2,y+1));
		if(y-1>-1) 	movements[3].push_back(Cell(x+2,y-1));
	}
	if(y-2>-1)
	{
		if(x+1<8) 	movements[4].push_back(Cell(x+1,y-2));
		if(x-1>-1) 	movements[5].push_back(Cell(x-1,y-2));
	}
	if(x-2>-1)
	{
		if(y-1>-1) 	movements[6].push_back(Cell(x-2,y-1));
		if(y+1<8) 	movements[7].push_back(Cell(x-2,y+1));
	}*/
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS BISHOP -----------------------------------------------------------
//------------------------------------------------------------------------------------------------------

Bishop::Bishop(unsigned int x, unsigned int y) : Piece(x,y)
{
	label = "B";
	/*
	int xx = x-1;
	int yy = y+1;
	while(xx>-1&&yy<8){
		movements[0].push_back(Cell(xx,yy));
		xx = xx-1;
		yy = yy+1;
	}
	xx = x+1;
	yy = y+1;
	while(xx<8&&yy<8){
		movements[1].push_back(Cell(xx,yy));
		xx = xx+1;
		yy = yy+1;
	}*/
}

//------------------------------------------------------------------------------------------------------
Bishop::~Bishop(){}

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void Bishop::movement()
{/*
	movements.clear();
	int x=square->getX();
	int y=square->getY();
	int xx = x-1;
	int yy = y+1;
	while(xx>-1&&yy<8){
		movements[0].push_back(Cell(xx,yy));
		xx = xx-1;
		yy = yy+1;
	}
	xx = x+1;
	yy = y+1;
	while(xx<8&&yy<8){
		movements[1].push_back(Cell(xx,yy));
		xx = xx+1;
		yy = yy+1;
	}
	xx = x+1;
	yy = y-1;
	while(xx<8&&yy>-1){
		movements[2].push_back(Cell(xx,yy));
		xx = xx+1;
		yy = yy-1;
	}
	xx = x-1;
	yy = y-1;
	while(xx>-1&&yy>-1){
		movements[3].push_back(Cell(xx,yy));
		xx = xx-1;
		yy = yy-1;
	}*/
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS QUEEN ------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

Queen::Queen(unsigned int x, unsigned int y) : Piece(x,y)
{
	label = "Q";
	/*
	int i;
	for(i = 1; i < 8 ; ++i)
	{
		movements[0].push_back(Cell(x,i));
	};
	int xx = x+1;
	int yy = y+1;
	while(xx<8&&yy<8){
		movements[1].push_back(Cell(xx,yy));
		xx = xx+1;
		yy = yy+1;
	}
	for(i = 1; i < 8 ; ++i)
	{
		movements[2].push_back(Cell(i+x,0));
	};
	for(i = 1; i < 8 ; ++i)
	{
		movements[3].push_back(Cell(x-i,0));
	};
	xx = x-1;
	yy = y+1;
	while(xx>-1&&yy<8){
		movements[4].push_back(Cell(xx,yy));
		xx = xx-1;
		yy = yy+1;
	}*/

}

//------------------------------------------------------------------------------------------------------
Queen::~Queen(){}

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void Queen::movement()
{/*
	movements.clear();
	int x=square->getX();
	int y=square->getY();
	int i,xx,yy;
	// mouvement comme la tour vers le haut
	for (i=1; y+i < 8 ; ++i)
	{
		movements[0].push_back(Cell(x,y+i));
	} 
	// mouvement comme le fou vers haut droite
	xx = x+1;
	yy = y+1;
	while(xx<8&&yy<8){
		movements[1].push_back(Cell(xx,yy));
		xx = xx+1;
		yy = yy+1;
	}
	// mouvement comme la tour vers la droite
	for (i=1; x+i < 8 ; ++i)
	{
		movements[2].push_back(Cell(x+i,y));
	}
	//mouvement comme le fou vers bas droite
	xx = x+1;
	yy = y-1;
	while(xx<8&&yy>-1){
		movements[3].push_back(Cell(xx,yy));
		xx = xx+1;
		yy = yy-1;
	}
	//mouvement comme la tour vers le bas
	for (i=1; y-i > -1 ; ++i)
	{
		movements[4].push_back(Cell(x,y-i));
	}
	// mouvement comme le fou vers bas gauche
	xx = x-1;
	yy = y-1;
	while(xx>-1&&yy>-1){
		movements[5].push_back(Cell(xx,yy));
		xx = xx-1;
		yy = yy-1;
	}
	// mouvement comme la tour vers la gauche
	for (i=1; x-i > -1 ; ++i)
	{
		movements[6].push_back(Cell(x-i,y));
	}
	// mouvement comme le fou vers le haut gauche
	xx = x-1;
	yy = y+1;
	while(xx>-1&&yy<8){
		movements[7].push_back(Cell(xx,yy));
		xx = xx-1;
		yy = yy+1;
	}*/
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS KING -------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

King::King(unsigned int x, unsigned int y) : Piece(x,y), _moved(0)
{
	label = "K";
	/*
	movements[0].push_back(Cell(4,1));
	movements[1].push_back(Cell(5,1));
	movements[2].push_back(Cell(5,0));
	movements[3].push_back(Cell(3,0));
	movements[4].push_back(Cell(3,1));*/
}

//------------------------------------------------------------------------------------------------------
King::~King(){}

//------------------------------------------------------------------------------------------------------
bool King::asMoved()
{
	return _moved;
}

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void King::movement()
{/*
	movements.clear();
	int x=square->getX();
	int y=square->getY();
	if ( x>0 ) 
	{
		if (y>0) 	movements[0].push_back(Cell(x-1,y-1));
		if (y<7)	movements[1].push_back(Cell(x-1,y+1));
		movements[2].push_back(Cell(x-1,y));
	}
	if ( x<7 )
	{
		if (y>0) 	movements[3].push_back(Cell(x+1,y-1));
		if (y<7)	movements[4].push_back(Cell(x+1,y+1));
		movements[5].push_back(Cell(x+1,y));
	}
	if (y>0) 	movements[6].push_back(Cell(x,y-1));
	if (y<7)	movements[7].push_back(Cell(x,y+1));*/
}
