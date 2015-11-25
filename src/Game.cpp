#include <iostream>
#include <string>
#include "Chess.hpp"
// #include "Console.hpp"

int main()
{
	Chess* chess;
	bool fin = false;
	int choose;
	std::string nomP1, nomP2;
	while (!fin){
		std::cout<<" Veuillez saisir votre choix ?"<<std::endl;
		std::cout<<" 1 pour lancer une partie "<<std::endl;
		std::cout<<" 2 pour quitter le programme "<<std::endl;
		std::cin>>choose;
		while(choose<1||choose>2)
		{
			std::cout<<" Veuillez choisir 1 ou 2 !"<<std::endl;
			std::cin>>choose;
		}
		switch(choose){
			case 1 :
			{
				std::cout<<" Veuillez saisir les deux prénoms des joueurs."<<std::endl;
				std::cin>>nomP1;
				std::cin>>nomP2;
				chess = new Chess(nomP1,nomP2);
				std::cout<<"le premier à jouer sera "<<nomP1<< " et il représentera les pions blancs."<<std::endl;
				std::cout<<"Ainsi, "<<nomP2<<" jouera en deuxième et il représentera les pions rouges."<<std::endl;
				std::cout<<" A vous de jouer ! Nous vous souhaitons bonne chance à vous deux ! :D "<<std::endl;
				chess->startGame();	
				break;
			}
			case 2 :
			{
				fin=true;
				std::cout<<" Nous vous remercions d'avoir jouer a notre jeu et nous vous disons : A BIENTOT !"<<std::endl;
				break;
			}
		}
	}
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
