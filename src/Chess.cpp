/**
* @file Chess.cpp
* @author P. Sullivan, G.Laurent
* @since 25/12/2015
* @brief implémentation des méthodes de la classe Chess
*
**/

#include "Chess.hpp"

//------------------------------------------------------------------------------------------------------
Chess::Chess(std::string nameP1, std::string nameP2)
{
	p1 = new Player(nameP1,"White");
	p2 = new Player(nameP2,"Black");
	initBoard();
}

//------------------------------------------------------------------------------------------------------
Chess::~Chess() {}

//------------------------------------------------------------------------------------------------------
void Chess::initBoard()
{
	unsigned int i, j;

	for(i = 0; i < 8 ; ++i)
	{
		for(j = 0 ; j < 8 ; ++j)
			_board[i][j] = new Piece(i,j);
	}
	
	for(i = 0 ; i < 8 ; ++i)
	{
		_board[i][1] = p1->getPieces()[i];			// Pions Blancs
		_board[i][0] = p1->getPieces()[i+8];		// Autre pièces Blanches

		_board[i][6] = p2->getPieces()[i];			// Pions Noirs
		_board[i][7] = p2->getPieces()[i+8];		// Autres pièces Noires
	}
}

//------------------------------------------------------------------------------------------------------
Piece* Chess::selectDest(Player* p, unsigned int x, unsigned int y)
{
	unsigned int i;

	for(i = 0 ; i < 16 ; ++i)
	{
		if( _board[x][y]->getSquare() == p->getPieces()[i]->getSquare() )		// Si la case selectionnée correspond à une pièce que le joueur p possède
			return NULL;
	}

	return _board[x][y];
}

//------------------------------------------------------------------------------------------------------
void Chess::gameRound(Player* playerIG, Player* advers)
{
	Piece* selectedP;
	Piece* selectedD;
	unsigned int x, y, x2, y2;

	std::cout << "Coordonnées de la pièce que vous voulez selectionner : " << std::endl;
	std::cout << "x: ";
	x = getChoiceInt();
	std::cout << "y: ";
	y = getChoiceInt();

	selectedP = playerIG->selectPiece(x,y);		// Selection de la pièce

	while(selectedP == NULL)
	{
		std::cout << "Aucune pièce en votre possession ne se situe sur la case : (" << x << "," << y << ")" << std::endl;

		std::cout << "Entrer des nouvelles coordonnées : " << std::endl;
		std::cout << "x: ";
		x = getChoiceInt();
		std::cout << "y: ";
		y = getChoiceInt();

		selectedP = playerIG->selectPiece(x,y);
	}

	std::cout << "Vous avez selectionné la pièce :" << std::endl;
	selectedP->printPiece();

	std::cout << "Coordonnées de la case sur laquelle vous voulez déplacer la pièce : " << std::endl;
	std::cout << "x: ";
	x2 = getChoiceInt();
	std::cout << "y: ";
	y2 = getChoiceInt();

	// Selection valide de la destination
	selectedD = selectDest(playerIG, x2,y2); 	
	while(selectedD == NULL)
	{
		std::cout << "Entrée de nouvelles coordonnées pour la destination de la pièce : " << std::endl;
		std::cout << "x: ";
		x2 = getChoiceInt();
		std::cout << "y: ";
		y2 = getChoiceInt();
		selectedD = selectDest(playerIG, x2,y2);
	}
}

//------------------------------------------------------------------------------------------------------
unsigned int Chess::getChoiceInt()
{
	unsigned int choice = 0;

	do
	{
		std::cin >> choice;
	}while(choice > 7);

	return choice;
}

//------------------------------------------------------------------------------------------------------
void Chess::printBoard()
{
	unsigned int i, j, k;

	for(i = 0; i < 8 ; ++i)
	{
		std::cout << 7-i<<"  |";
		for(j = 0 ; j < 8 ; ++j)
			std::cout << _board[j][7-i]->getLabel() << "|";

		std::cout << std::endl;
	}
	
  	std::cout <<"y/x ";

	for(k = 0; k < 8 ; ++k)
		std::cout << k <<" ";

	std::cout << std::endl;
}

//------------------------------------------------------------------------------------------------------
void Chess::startGame()
{
	gameRound(p1, p2);
}