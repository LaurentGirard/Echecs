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
std::vector< std::vector< Cell> > Piece::getmovements()
{
	return movements;
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS Spawn -------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

Spawn::Spawn(unsigned int x, unsigned int y, bool direction) : Piece(x,y), _direction(direction)
{
	label = "S";

	std::vector< Cell> mov; // vecteur de cell afin de l'ajouter ensuite dans movements

	if (_direction == true)
	{
		mov.push_back(Cell(x,y-1));
		mov.push_back(Cell(x,y-2));
		if(x<7)
		{
			_caneat.push_back(Cell(x+1, y-1));
		}
		if(x>0)
		{
			_caneat.push_back(Cell(x-1, y-1));
		}
	}
	else
	{
		mov.push_back(Cell(x,y+1));
		mov.push_back(Cell(x,y+2));
		if(x<7)
		{
			_caneat.push_back(Cell(x+1, y+1));
		}
		if(x>0)
		{
			_caneat.push_back(Cell(x-1, y+1));
		}
	}
	movements.push_back(mov);
}

//------------------------------------------------------------------------------------------------------
Spawn::~Spawn(){}

//------------------------------------------------------------------------------------------------------
void Spawn::movement()
{	
	movements.clear();
	_caneat.clear();
	std::vector< Cell> mov; // vecteur de cell afin de l'ajouter ensuite dans movements
	
	if (_direction == true)
	{
		if(square->getY()>-1) mov.push_back(Cell(square->getX(),square->getY()-1));
		_caneat.push_back(Cell(square->getX()-1,square->getY()-1));
		_caneat.push_back(Cell(square->getX()+1,square->getY()-1));
	}
	else
	{
		if(square->getY()<7) mov.push_back(Cell(square->getX(),square->getY()+1));
		_caneat.push_back(Cell(square->getX()-1,square->getY()+1));
		_caneat.push_back(Cell(square->getX()+1,square->getY()+1));
	}
	movements.push_back(mov);
}

//------------------------------------------------------------------------------------------------------
std::vector< Cell> Spawn::getcaneat()
{
	return _caneat;
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS ROOK -------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

Rook::Rook(unsigned int x, unsigned int y) : Piece(x,y), _moved(0)
{
	label = "R";
	movement();
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
void Rook::movement()
{
	movements.clear();
	std::vector< Cell> mov; // vecteur de cell afin de l'ajouter ensuite dans movements
	mov.clear();
	unsigned int x = square->getX();
	unsigned int y = square->getY();
	unsigned int i;

	for (i = 1; x+i < 8 ; ++i)
		mov.push_back(Cell(x+i,y));

	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}

	for (i = 1; x-i > -1 ; ++i)
		mov.push_back(Cell(x-i,y));

	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}

	for (i = 1; y+i < 8 ; ++i)
		mov.push_back(Cell(x,y+i));

	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}

	for (i = 1; y-i > -1 ; ++i)
		mov.push_back(Cell(x,y-i));

	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS KNIGHT -----------------------------------------------------------
//------------------------------------------------------------------------------------------------------

Knight::Knight(unsigned int x, unsigned int y) : Piece(x,y)
{
	label = "C";
	movement();
}

//------------------------------------------------------------------------------------------------------
Knight::~Knight(){}

//------------------------------------------------------------------------------------------------------
void Knight::movement()
{
	std::vector< Cell> mov; // vecteur de cell afin de l'ajouter ensuite dans movements
	mov.clear();
	movements.clear();
	unsigned int x = square->getX();
	unsigned int y = square->getY();

	if(y+2 < 8)
	{
		if(x-1 > -1)
		{
			mov.push_back(Cell(x-1,y+2));
			movements.push_back(mov);
			mov.clear();
		}
		if(x+1 < 8)
		{
			mov.push_back(Cell(x+1,y+2));
			movements.push_back(mov);
			mov.clear();
		}
	}
	if(x+2 < 8)
	{
		if(y+1 < 8) 	
		{
			mov.push_back(Cell(x+2,y+1));
			movements.push_back(mov);
			mov.clear();
		}
		if(y-1 > -1) 	
		{
			mov.push_back(Cell(x+2,y-1));
			movements.push_back(mov);
			mov.clear();
		}
	}
	if(y-2 > -1)
	{
		if(x+1 < 8) 	
		{
			mov.push_back(Cell(x+1,y-2));
			movements.push_back(mov);
			mov.clear();
		}
		if(x-1 > -1) 	
		{
			mov.push_back(Cell(x-1,y-2));
			movements.push_back(mov);
			mov.clear();
		}
	}
	if(x-2 > -1)
	{
		if(y-1 > -1) 	
		{
			mov.push_back(Cell(x-2,y-1));
			movements.push_back(mov);
			mov.clear();
		}
		if(y+1 < 8) 	
		{
			mov.push_back(Cell(x-2,y+1));
			movements.push_back(mov);
			mov.clear();
		}
	}
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS BISHOP -----------------------------------------------------------
//------------------------------------------------------------------------------------------------------

Bishop::Bishop(unsigned int x, unsigned int y) : Piece(x,y)
{
	label = "B";
	movement();
}

//------------------------------------------------------------------------------------------------------
Bishop::~Bishop(){}

//------------------------------------------------------------------------------------------------------
void Bishop::movement()
{
	std::vector< Cell> mov; // vecteur de cell afin de l'ajouter ensuite dans movements
	mov.clear();
	movements.clear();
	unsigned int x=square->getX();
	unsigned int y=square->getY();
	unsigned int xx = x-1;
	unsigned int yy = y+1;

	while(xx > -1 && yy < 8)
	{
		mov.push_back(Cell(xx,yy));
		xx = xx-1;
		yy = yy+1;
	}

	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}

	xx = x+1;
	yy = y+1;

	while(xx < 8 && yy < 8)
	{
		mov.push_back(Cell(xx,yy));
		xx = xx+1;
		yy = yy+1;
	}
	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}

	xx = x+1;
	yy = y-1;

	while(xx < 8 && yy > -1)
	{
		mov.push_back(Cell(xx,yy));
		xx = xx+1;
		yy = yy-1;
	}

	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}

	xx = x-1;
	yy = y-1;

	while(xx > -1 && yy > -1)
	{
		mov.push_back(Cell(xx,yy));
		xx = xx-1;
		yy = yy-1;
	}
	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS QUEEN ------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

Queen::Queen(unsigned int x, unsigned int y) : Piece(x,y)
{
	label = "Q";
	movement();
}

//------------------------------------------------------------------------------------------------------
Queen::~Queen(){}

//------------------------------------------------------------------------------------------------------
void Queen::movement()
{
	std::vector< Cell> mov; // vecteur de cell afin de l'ajouter ensuite dans movements
	mov.clear();
	movements.clear();
	unsigned int x = square->getX();
	unsigned int y = square->getY();
	unsigned int i, xx, yy;
	// mouvement comme la tour vers le haut
	for (i = 1; y+i < 8 ; ++i)
		mov.push_back(Cell(x,y+i));

	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}
	// mouvement comme le fou vers haut droite
	xx = x+1;
	yy = y+1;

	while(xx < 8 && yy < 8)
	{
		mov.push_back(Cell(xx,yy));
		xx = xx+1;
		yy = yy+1;
	}

	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}

	// mouvement comme la tour vers la droite
	for (i = 1; x+i < 8 ; ++i)
		mov.push_back(Cell(x+i,y));

	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}
	//mouvement comme le fou vers bas droite
	xx = x+1;
	yy = y-1;
	while(xx < 8 && yy > -1)
	{
		mov.push_back(Cell(xx,yy));
		xx = xx+1;
		yy = yy-1;
	}

	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}
	//mouvement comme la tour vers le bas
	for (i = 1; y-i > -1 ; ++i)
		mov.push_back(Cell(x,y-i));

	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}
	// mouvement comme le fou vers bas gauche
	xx = x-1;
	yy = y-1;

	while(xx >- 1 && yy > -1)
	{
		mov.push_back(Cell(xx,yy));
		xx = xx-1;
		yy = yy-1;
	}
	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}
	// mouvement comme la tour vers la gauche
	for (i = 1; x-i > -1 ; ++i)
		mov.push_back(Cell(x-i,y));

	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}
	// mouvement comme le fou vers le haut gauche
	xx = x-1;
	yy = y+1;

	while(xx >- 1 && yy < 8)
	{
		mov.push_back(Cell(xx,yy));
		xx = xx-1;
		yy = yy+1;
	}

	if(mov.size() > 0)
	{
		movements.push_back(mov);
		mov.clear();
	}
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS KING -------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

King::King(unsigned int x, unsigned int y) : Piece(x,y), _moved(0)
{
	label = "K";
	movement();
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
{
	std::vector< Cell> mov; // vecteur de cell afin de l'ajouter ensuite dans movements
	mov.clear();
	movements.clear();
	unsigned int x=square->getX();
	unsigned int y=square->getY();

	if (x > 0) 
	{
		if (y > 0)
		{
			mov.push_back(Cell(x-1,y-1));
			movements.push_back(mov);
			mov.clear();
		}
		if (y < 7)	
		{
			mov.push_back(Cell(x-1,y+1));
			movements.push_back(mov);
			mov.clear();
		}
		mov.push_back(Cell(x-1,y));
		movements.push_back(mov);
		mov.clear();
	}
	if (x < 7)
	{
		if (y > 0) 	
		{
			mov.push_back(Cell(x+1,y-1));
			movements.push_back(mov);
			mov.clear();
		}
		if (y < 7)	
		{
			mov.push_back(Cell(x+1,y+1));
			movements.push_back(mov);
			mov.clear();
		}
		mov.push_back(Cell(x+1,y));
		movements.push_back(mov);
		mov.clear();
	}
	if (y > 0) 	
	{
		mov.push_back(Cell(x,y-1));
		movements.push_back(mov);
		mov.clear();
	}
	if (y < 7)	
	{
		mov.push_back(Cell(x,y+1));
		movements.push_back(mov);
		mov.clear();
	}
}
