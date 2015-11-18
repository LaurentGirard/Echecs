/**
* @file State.cpp
* @author P. Sullivan, G.Laurent
* @since 25/12/2015
* @brief implémentation des méthodes de la classe State ainsi que de ses classes filles
**/

#include "State.hpp"
#include "Player.hpp"

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS STATE ------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

State::State(Player* p) : player(p) {}
//------------------------------------------------------------------------------------------------------
State::~State(){}

//------------------------------------------------------------------------------------------------------
void State::inGame(){}

//------------------------------------------------------------------------------------------------------
void State::check(){}

//------------------------------------------------------------------------------------------------------
void State::checkMate(){}

//------------------------------------------------------------------------------------------------------
void State::gameNull(){}

//------------------------------------------------------------------------------------------------------
void State::gameEnd(){}

//------------------------------------------------------------------------------------------------------
void State::print(){}


//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS GAMESTATE --------------------------------------------------------
//------------------------------------------------------------------------------------------------------

GameState::GameState(Player* p) : State(p) {}

//------------------------------------------------------------------------------------------------------
GameState::~GameState(){}

//------------------------------------------------------------------------------------------------------
void GameState::inGame()
{
	std::cout << "Le joueur " << player->getName() << " est déjà en état de jeu !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void GameState::check()
{
	player->setState(player->getCheckState());
}

//------------------------------------------------------------------------------------------------------
void GameState::checkMate()
{
	player->setState(player->getMateState());
}

//------------------------------------------------------------------------------------------------------
void GameState::gameNull()
{
	player->setState(player->getNullState());
}	

//------------------------------------------------------------------------------------------------------
void GameState::gameEnd()
{
	std::cout << "Le joueur " << player->getName() << " est encore en état de jeu !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void GameState::print()
{
	std::cout << "En jeu" << std::endl;
}


//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS CHECKSTATE --------------------------------------------------------
//------------------------------------------------------------------------------------------------------

CheckState::CheckState(Player* p) : State(p) {}

//------------------------------------------------------------------------------------------------------
CheckState::~CheckState(){}

//------------------------------------------------------------------------------------------------------
void CheckState::inGame()
{
	player->setState(player->getGameState());
}

//------------------------------------------------------------------------------------------------------
void CheckState::check()
{
	std::cout << "Le joueur " << player->getName() << " est déjà en état d'échec !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void CheckState::checkMate()
{
	std::cout << "Le joueur " << player->getName() << " ne peut pas passer en état d'échec et mat !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void CheckState::gameNull()
{
	std::cout << "Le joueur " << player->getName() << " ne peut pas passer en état de jeu nul !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void CheckState::gameEnd()
{
	std::cout << "Le joueur " << player->getName() << " est encore en état d'échec et ne peut donc pas finir la partie !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void CheckState::print()
{
	std::cout << "Echec" << std::endl;
}


//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS MATESTATE --------------------------------------------------------
//------------------------------------------------------------------------------------------------------

MateState::MateState(Player* p): State(p) {}

//------------------------------------------------------------------------------------------------------
MateState::~MateState(){}

//------------------------------------------------------------------------------------------------------
void MateState::inGame()
{
	std::cout << "Le joueur " << player->getName() << " est en état d'échec et mat, il ne peut donc pas revenir en jeu !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void MateState::check()
{
	std::cout << "Le joueur " << player->getName() << " est en état d'échec et mat, il ne peut donc pas être en échec !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void MateState::checkMate()
{
	std::cout << "Le joueur " << player->getName() << " est déjà en état d'échec et mat !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void MateState::gameNull()
{
	std::cout << "Le joueur " << player->getName() << " ne peut pas passer en état de jeu nul !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void MateState::gameEnd()
{
	player->setState(player->getEndState());
}

//------------------------------------------------------------------------------------------------------
void MateState::print()
{
	std::cout << "Echec et mat" << std::endl;
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS NULLSTATE --------------------------------------------------------
//------------------------------------------------------------------------------------------------------

NullState::NullState(Player* p) : State(p) {}

//------------------------------------------------------------------------------------------------------
NullState::~NullState(){}

//------------------------------------------------------------------------------------------------------
void NullState::inGame()
{
	std::cout << "Le joueur " << player->getName() << " est en état de jeu nul, il ne peut donc pas revenir en jeu !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void NullState::check()
{
	std::cout << "Le joueur " << player->getName() << " est en état de jeu nul, il ne peut donc pas être en échec !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void NullState::checkMate()
{
	std::cout << "Le joueur " << player->getName() << " est en état de jeu nul, il ne peut donc pas être échec et mat!" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void NullState::gameNull()
{
	std::cout << "Le joueur " << player->getName() << " est déjà en jeu nul !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void NullState::gameEnd()
{
	player->setState(player->getEndState());
}

//------------------------------------------------------------------------------------------------------
void NullState::print()
{
	std::cout << "Jeu nul" << std::endl;
}

//------------------------------------------------------------------------------------------------------
//----------------------------- CLASS ENDSTATE --------------------------------------------------------
//------------------------------------------------------------------------------------------------------

EndState::EndState(Player* p): State(p) {}

//------------------------------------------------------------------------------------------------------
EndState::~EndState(){}

//------------------------------------------------------------------------------------------------------
void EndState::inGame()
{
	std::cout << "Le joueur " << player->getName() << " est en état de jeu terminé, il ne peut donc pas revenir en jeu !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void EndState::check()
{
	std::cout << "Le joueur " << player->getName() << " est en état de jeu terminé, il ne peut donc pas être en échec !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void EndState::checkMate()
{
	std::cout << "Le joueur " << player->getName() << " est en état de jeu terminé, il ne peut donc pas être échec et mat !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void EndState::gameNull()
{
	std::cout << "Le joueur " << player->getName() << " est en état de jeu terminé, il ne peut donc pas être en jeu nul !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void EndState::gameEnd()
{
	std::cout << "Le joueur " << player->getName() << " est déjà en état de jeu terminé !" << std::endl;
}

//------------------------------------------------------------------------------------------------------
void EndState::print()
{
	std::cout << "Jeu terminé" << std::endl;
}

