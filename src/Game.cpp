#include <iostream>
#include <cstdlib>
#include <string>
#include "Chess.hpp"

int main()
{
	Chess* chess;
	bool fin = false;
	unsigned int choose;
	std::string nomP1, nomP2;
	int value_returned;

	// Permet de clear la sortie standard en affichant un message s'il y a eu une erreur
	value_returned = std::system("clear");
	if(value_returned != 0)
	std::cout << "Problem Clear" << std::endl;

	while (!fin){
		std::cout << " Veuillez saisir votre choix ?" << std::endl;
		std::cout << " 1 pour lancer une partie " << std::endl;
		std::cout << " 2 pour quitter le programme " << std::endl;
		std::cin >> choose;

		while(choose < 1 || choose > 2)
		{
			std::cout << " Veuillez choisir 1 ou 2 !" << std::endl;
			std::cin >> choose;
		}
		switch(choose){
			case 1 :
			{
				std::cout << " Veuillez saisir les deux prénoms des joueurs." << std::endl;
				std::cin >> nomP1;
				std::cin >> nomP2;
				chess = new Chess(nomP1,nomP2);
				std::cout << std::endl;
				std::cout << nomP1 << " possède les pions blancs, il commencera la partie." << std::endl;
				std::cout << nomP2 << " possède donc les pions noirs, il jouera en second." << std::endl;
				std::cout << std::endl;
				std::cout << " A vous de jouer ! Nous vous souhaitons bonne chance ! :D " << std::endl;
				std::cout << std::endl;

				// Permet de faire une pause sur la sortie standard
				std::cin.ignore(1024, '\n');
				std::cout << " Appuyez sur une touche pour continuer";
				std::cin.get();

				// Permet de clear la sortie standard en affichant un message s'il y a eu une erreur
				value_returned = std::system("clear");
				if(value_returned != 0)
					std::cout << "Problem Clear" << std::endl;

				chess->startGame();	
				break;
			}
			case 2 :
			{
				fin = true;
				std::cout << " Nous vous remercions d'avoir joué, en espérant vous revoir bientôt !" << std::endl;
				break;
			}
		}
	}

	return 0;
}
