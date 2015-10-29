#include <iostream>
#include <string>
#include "Piece.cpp"
#include "Player.cpp"

// Piece** initBoard(Player playerA, Player playerB)
// {
// 	Piece** board = new Piece*[8];

// 	unsigned int i, j;

// 	for(i = 0 ; i < 8 ; ++i)
// 	{
// 		for(j = 0 ; j < 8 ; ++j)
// 			board[i] = new Piece(i,j);
// 	}

// 	for(i = 0 ; i < 8 ; ++i)
// 	{
// 		board[6][i] = playerA.getPieces()[i];		// Pions Blancs
// 		board[7][i] = playerA.getPieces()[i+8];		// Autre pièces Blanches

// 		board[1][i] = playerB.getPieces()[i];		// Pions Noirs
// 		board[0][i] = playerB.getPieces()[i+8];		// Autres pièces Noires
// 	}

// 	return board;
// }


int main()
{
	Piece* board[8][8]; // A revoir !!!!!!!!!!!!!!!! pas bien !

	Player playerA("Alfred","White");
	Player playerB("Alphonse","Black");
	
	unsigned int i, j;

	// initialisation tableau
	for(i = 0; i < 8 ; ++i)
	{
		for(j = 0 ; j < 8 ; ++j)
		{
			board[i][j] = new Piece(i,j);
		}
	}
	
	for(i = 0 ; i < 8 ; ++i)
	{
		board[i][1] = playerA.getPieces()[i];		// Pions Blancs
		board[i][0] = playerA.getPieces()[i+8];		// Autre pièces Blanches -> à remettre dans l'ordre

		board[i][6] = playerB.getPieces()[i];		// Pions Noirs
		board[i][7] = playerB.getPieces()[i+8];		// Autres pièces Noires
	}

	// TESTS

	board[0][2] = playerA.getPieces()[1];				// Nouvelle case de la pièce sur le plateau
	playerA.getPieces()[1]->setSquare(new Cell(0,2));	// maj des coordonnées de la pièce
	board[0][1] = new Piece(0,1);						// remplace l'ancien emplacement de la pièce par une piece vide

	board[5][5] = playerB.getPieces()[5];
	playerA.getPieces()[1]->setSquare(new Cell(5,5));	// maj des coordonnées de la pièce
	board[5][6] = new Piece(5,6);

	// affichage
	for(i = 0; i < 8 ; ++i)
	{
		std::cout << "|";
		for(j = 0 ; j < 8 ; ++j)
			std::cout << board[i][j]->getLabel() << "|";

		std::cout << std::endl;
	}
	//affichage des déplacement possible d'une piece 
	for(int ww = 0; ww< playerA.getPieces()[12]->getmovements().size() ; ++ww)
	{
		for(int www = 0; www< playerA.getPieces()[12]->getmovements()[ww].size() ; ++www) 		
		std::cout << playerA.getPieces()[12]->getmovements()[ww][www].getX()<<" - "<<playerA.getPieces()[12]->getmovements()[ww][www].getY() << std::endl;
		
		std::cout << playerA.getPieces()[12]->getmovements()[ww].size()<< std::endl;
	};
	return 0;
}
