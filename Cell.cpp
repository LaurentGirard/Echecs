/**
* @file Cell.cpp
* @author P. Sullivan, G.Laurent
* @since 25/12/2015
* @brief implémentation des méthodes de la classe Cell
*
**/

#include "Cell.hpp"


//------------------------------------------------------------------------------------------------------
Cell::Cell(unsigned int x, unsigned int y)
{
	if(x < 8 && y < 8)		// Coordonnées valides pour un jeu d'echec < 8, type unsigned donc > 0
	{
		_x = x;
		_y = y;
	}
	else
		std::cout << "Erreur d'initialisation" << std::endl;
}

//------------------------------------------------------------------------------------------------------
Cell::~Cell(){}

//------------------------------------------------------------------------------------------------------
unsigned int Cell::getX()
{
	return _x;
}

//------------------------------------------------------------------------------------------------------
void Cell::setX(unsigned int newX)
{
	if(newX < 8)
		_x = newX;
	else
		std::cout << "Nouvelle coordonée " << newX << " invalide" << std::endl;
}

//------------------------------------------------------------------------------------------------------
unsigned int Cell::getY()
{
	return _y;
}

//------------------------------------------------------------------------------------------------------
void Cell::setY(unsigned int newY)
{
	if(newY < 8)
		_y = newY;
	else
		std::cout << "Nouvelle coordonée " << newY << " invalide" << std::endl;
}
