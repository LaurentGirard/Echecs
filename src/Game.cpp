#include <iostream>
#include <string>
#include "Chess.hpp"
// #include "Console.hpp"

int main()
{
	Chess* chess = new Chess("Alphonse","Alfred");
	
	chess->startGame();

	// // TESTS

	// board[0][2] = playerA.getPieces()[1];				// Nouvelle case de la pièce sur le plateau
	// playerA.getPieces()[1]->setSquare(new Cell(0,2));	// maj des coordonnées de la pièce
	// board[0][1] = new Piece(0,1);						// remplace l'ancien emplacement de la pièce par une piece vide

	// board[5][5] = playerB.getPieces()[5];
	// playerA.getPieces()[1]->setSquare(new Cell(5,5));	// maj des coordonnées de la pièce
	// board[5][6] = new Piece(5,6);


	//affichage des déplacement possible d'une piece 
	// for(int ww = 0; ww< playerB.getPieces()[1]->getcaneat().size() ; ++ww)
	// {	
	// 	std::cout << playerB.getPieces()[1]->getcaneat()[ww].getX()<<" - "<<playerB.getPieces()[1]->getcaneat()[ww].getY() << std::endl;

	// }

	return 0;
}
