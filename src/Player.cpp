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
	bool col;
	int i;
	Team* team = new Team();

	// Initialisation des différents états
	_gameState = new GameState(this);
	_checkState = new CheckState(this);
	_mateState = new MateState(this);
	_nullState = new NullState(this);
	_endState = new EndState(this);
	_state = _gameState;

	col = !( (color == "White") || (color == "Blanc") );


	for (i = 0; i < 16;++i)
		_pieces[i] = team->buildTeamNormal(col)[i];

	delete team;
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
Piece* Player::getKing()
{
	return _pieces[12];
}

//------------------------------------------------------------------------------------------------------
bool Player::isCheckMate()
{
	return _state->isCheckMate();
}
//------------------------------------------------------------------------------------------------------
bool Player::ischeck()
{
	return _state->ischeck();
}

//-------------------------------------------------------------------------------------------------------
bool Player::isnulle()
{
	return _state->isnulle();
}

