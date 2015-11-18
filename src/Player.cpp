/**
* @file Player.cpp
* @author P. Sullivan, G.Laurent
* @since 25/12/2015
* @brief implémentation des méthodes de la classe Player
*
**/

#include "Player.hpp"

//------------------------------------------------------------------------------------------------------
Player::Player(std::string name, std::string color) : _name(name), _color(color)
{
	// Initialisation des différents états
	_gameState = new GameState(this);
	_checkState = new CheckState(this);
	_mateState = new MateState(this);
	_nullState = new NullState(this);
	_endState = new EndState(this);
	_state = _gameState;

	// Initialisation des pièces du joueur en fonction de sa couleur
	unsigned int i;
	unsigned int ySpawn = 8;
	unsigned int yPieces = 8;

	if( (color == "White") || (color == "Blanc") )
	{
		ySpawn = 1;
		yPieces = 0;
	}
	else if( (color == "Black") || (color == "Noir") )
	{
		ySpawn = 6;
		yPieces = 7;
	}
	else
		std::cout << "Erreur d'initialisation, la couleur : " << color << " n'est pas valide !" << std::endl;

	for(i = 0; i < 8 ; ++i)
	{
		if ( (color == "White") || (color == "Blanc") )
			_pieces[i] = new Spawn(i,ySpawn,false);

		if( (color == "Black") || (color == "Noir") )
			_pieces[i] = new Spawn(i,ySpawn,true);
	}

	_pieces[8] = new Rook(0,yPieces);
	_pieces[9] = new Knight(1,yPieces);
	_pieces[10] = new Bishop(2,yPieces);
	_pieces[11] = new Queen(3,yPieces);
	_pieces[12] = new King(4,yPieces);
	_pieces[13] = new Bishop(5,yPieces);
	_pieces[14] = new Knight(6,yPieces);
	_pieces[15] = new Rook(7,yPieces);
}

//------------------------------------------------------------------------------------------------------
Player::~Player(){} // La destruction des différentes allocations est réalisée à la fin du programme automatiquement

//------------------------------------------------------------------------------------------------------
void Player::inGame()
{
	_state->inGame();
}

//------------------------------------------------------------------------------------------------------
void Player::check()
{
	_state->check();
}

//------------------------------------------------------------------------------------------------------
void Player::checkMate()
{
	_state->checkMate();
}

//------------------------------------------------------------------------------------------------------
void Player::gameNull()
{
	_state->gameNull();
}

//------------------------------------------------------------------------------------------------------
void Player::gameEnd()
{
	_state->gameEnd();
}

//------------------------------------------------------------------------------------------------------
void Player::printState()
{
	_state->print();
}
//------------------------------------------------------------------------------------------------------
void Player::printPieces()
{
	unsigned int i;

	std::cout << "Les pièces encore en vie sont :" << std::endl;

	for( i = 0 ; i < 16 ; ++i)
	{
		if (_pieces[i]->isAlive())
			_pieces[i]->printPiece();
	}
}

//------------------------------------------------------------------------------------------------------
Piece* Player::selectPiece(unsigned int x, unsigned int y)
{
	unsigned int i;

	for( i = 0 ; i < 16 ; ++i)
	{
		if( (_pieces[i]->getSquare()->getX() == x) && (_pieces[i]->getSquare()->getY() == y) && (_pieces[i]->isAlive()) )
			return _pieces[i];
	}

	return NULL;
}

//------------------------------------------------------------------------------------------------------
std::string Player::getName()
{
	return _name;
}

//------------------------------------------------------------------------------------------------------
void Player::setName(std::string newName)
{
	_name = newName;
}

//------------------------------------------------------------------------------------------------------
std::string Player::getColor()
{
	return _color;
}
//------------------------------------------------------------------------------------------------------
Piece** Player::getPieces()
{
	return _pieces;
}
//------------------------------------------------------------------------------------------------------
State* Player::getState()
{
	return _state;
}

//------------------------------------------------------------------------------------------------------
void Player::setState(State *newState)
{
	_state = newState;
}

//------------------------------------------------------------------------------------------------------
State* Player::getGameState()
{
	return _gameState;
}

//------------------------------------------------------------------------------------------------------
State* Player::getCheckState()
{
	return _checkState;
}

//------------------------------------------------------------------------------------------------------
State* Player::getMateState()
{
	return _mateState;
}

//------------------------------------------------------------------------------------------------------
State* Player::getNullState()
{
	return _nullState;
}

//------------------------------------------------------------------------------------------------------
State* Player::getEndState()
{
	return _endState;
}

//------------------------------------------------------------------------------------------------------
Piece* Player::getking()
{
	return _pieces[12];
}

//------------------------------------------------------------------------------------------------------
bool Player::ischeckmate()
{
	return _state->ischeckmate();
}
//------------------------------------------------------------------------------------------------------
bool Player::ischeck()
{
	return _state->ischeck();
}
