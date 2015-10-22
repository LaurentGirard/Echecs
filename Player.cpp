/**
* @file Player.cpp
* @author P. Sullivan, G.Laurent
* @since 25/12/2015
* @brief implémentation des méthodes de la classe Player
*
**/

#include "Player.hpp"
// #include "State.cpp"

//------------------------------------------------------------------------------------------------------
Player::Player(std::string name) : 	_name(name)
									// _gameState(new GameState(this)), 
									// _checkState((new CheckState(this)), 
									// _mateState(new MateState(this)),
									// _nullState(new NullState(this)),
									// _endState(new EndState(this)),
									// _state(_gameState)
									{}

//------------------------------------------------------------------------------------------------------
Player::~Player(){}

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