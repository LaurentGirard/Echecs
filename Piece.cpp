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

Piece::Piece(std::string color) : alive(true), color(color){}

//------------------------------------------------------------------------------------------------------
Piece::~Piece(){}

//------------------------------------------------------------------------------------------------------
Cell Piece::getSquare()
{
	return square;
}

//------------------------------------------------------------------------------------------------------
void Piece::setSquare(Cell newCell)
{
	square.setX(newCell.getX());
	square.setY(newCell.getY());
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
void Piece::printPiece()
{
	std::cout << "Color : " << color << std::endl;
	std::cout << "X position : " << square.getX() << std::endl;
	std::cout << "Y position : " << square.getY() << std::endl;
}

//------------------------------------------------------------------------------------------------------
void Piece::move(Cell const dest){}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS KING ------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

King::King(std::string color) : Piece(color), _moved(0)
{
	if(color == "white")
		square.setY(0);
	else if(color == "black")
		square.setY(7);
	else
		std::cout << "Erreur d'initialisation" << std::endl;

	square.setX(3);
}

//------------------------------------------------------------------------------------------------------
King::~King(){}

//------------------------------------------------------------------------------------------------------
bool King::asMoved()
{
	return _moved;
}

//------------------------------------------------------------------------------------------------------
void King::setMoved(bool newMoved)
{
	_moved = newMoved;
}

//------------------------------------------------------------------------------------------------------
void King::move(Cell const dest)
{
    square.setX(dest.getX());
    square.setY(dest.getY());
}

//------------------------------------------------------------------------------------------------------
bool King::destination(Cell const dest)
{
	if( dest.getX()-square.getX() = 1 && dest.getY()-square.getY()>-2 && dest.getY()-square.getY()<2)
		return true
	else if( dest.getX()-square.getX() = 0 && (dest.getY()-square.getY()==1 || dest.getY()-square.getY()==-1) )
        return true
    else if( dest.getX()-square.getX() = -1 && dest.getY()-square.getY()>-2 && dest.getY()-square.getY()<2)
        return true
    else
        return false
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS CAVALIER ------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

CAVALIER::CAVALIER(std::string color, int num) : Piece(color),
{
    
    if ( num == 1)		
        square.setX(1);
    else if ( num == 2)
        square.setX(6);
	else
		std::cout << "Erreur d'initialisation" << std::endl;
	if(color == "white")
        square.setY(0);
    else if(color == "black")
	    square.setY(7);
	else
		std::cout << "Erreur d'initialisation" << std::endl;

}

//------------------------------------------------------------------------------------------------------
CAVALIER::~CAVALIER(){}

//------------------------------------------------------------------------------------------------------
void CAVALIER::move(Cell const dest)
{
    /*square.setX(dest.getX());
    square.setY(dest.getY());*/
}

//------------------------------------------------------------------------------------------------------
bool CAVALIER::destination(Cell const dest)
{
	/*if( dest.getX()-square.getX() = 1 && dest.getY()-square.getY()>-2 && dest.getY()-square.getY()<2)
		return true
	else if( dest.getX()-square.getX() = 0 && (dest.getY()-square.getY()==1 || dest.getY()-square.getY()==-1) )
        return true
    else if( dest.getX()-square.getX() = -1 && dest.getY()-square.getY()>-2 && dest.getY()-square.getY()<2)
        return true
    else*/
        return false
}
