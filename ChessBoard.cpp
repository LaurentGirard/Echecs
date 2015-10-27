/**
* @file ChessBoard.cpp
* @author P. Sullivan, G.Laurent
* @since 25/12/2015
* @brief implémentation des méthodes de la classe ChessBoard
**/

#include "ChessBoard.hpp"


ChessBoard::ChessBoard(std::string namePA, std::string namePB)
{
	_playerA = new Player(namePA,"White");
	_playerB = new Player(namePB,"Black");
}

//------------------------------------------------------------------------------------------------------
ChessBoard::~ChessBoard(){}

//------------------------------------------------------------------------------------------------------
Piece* ChessBoard::getChessBoard()
{
	return _board;
}

//------------------------------------------------------------------------------------------------------
Player* ChessBoard::getPlayerA()
{
	return _playerA;
}

//------------------------------------------------------------------------------------------------------
Player* ChessBoard::getPlayerB()
{
	return _playerB;
}