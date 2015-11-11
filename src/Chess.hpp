/**
 * @file Chess.hpp
 * @author P. Sullivan, G.Laurent
 * @since 25/12/2015
 * @brief Définition de la classe Chess, permettant aux deux joueurs d'intéragir sur le plateau
 *
**/

#ifndef __CHESS_HPP__
#define __CHESS_HPP__

#include "Player.hpp"

class Chess
{
	private:
		Player* p1;				// Attribut : Joueur 1
		Player* p2;				// Attribut : Joueur 2
		Piece* _board[8][8];		// Plateau de pièces

	public:

		/**
       * @brief Constructeur, crée un objet Chess
       * @param string nameP1
       * @param string nameP2
       */
			Chess(std::string nameP1, std::string nameP2);

      	/**
       * @brief Destructeur de Chess
       */
			~Chess();

		/**
		* @brief Initialise le plateau de jeu
		*/
			void initBoard();

		/**
		* @brief Permet au joueur de selectionner une destination pour son déplacement de pièce
		* @param unsigned int x, coordonnée x de la case selectionnée
		* @param unsigned int y, coordonnée y de la case selectionnée
		* @param Player* player, pointeur vers le joueur en jeu
		* @param Piece* piece, pointeur de la pièce que le joueur veut déplacer
		* @return Piece* pointeur de la destination selectionnée sur le plateau (le board étant un tableau de Piece)
		*/
			Piece* selectDest(Player* player, Piece* piece, unsigned int x, unsigned int y);

		/**
		* @brief Vérifie s'il n'y a pas de collision lors du déplacement de la pièce vers la destination sélectionée
		* @param Player* player, pointeur vers le joueur en jeu
		* @param Piece* selectedP, pointeur vers la pièce selectionnée
		* @param Piece* selectedD, pointeur vers la pièce représentant la destination
		* @return bool, vrai s'il n'y a pas de collision, faux sinon
		*/
			bool noCollision(Player* player, Piece* selectedP, Piece* selectedD);

		/**
		* @brief Effectue le déplacement de la pièce selectionnée vers la destination
		* @param Player* player, pointeur vers le joueur en jeu
		* @param Piece* selectedP, pointeur vers la pièce selectionnée
		* @param Piece* selectedD, pointeur vers la pièce représentant la destination
		*/
			void movePiece(Player* player, Piece* selectedP, Piece* selectedD);

		/**
		* @brief Effectue le tour d'un joueur
		* @param Player* playerIG, Joueur actuellement en jeu
		* @param Player* adver, Joueur en attente de jouer
		*/
			void gameRound(Player* playerIG, Player* adver);

		/**
		* @brief Permet l'entrée utilisateur d'une coordonnée valide
		* @return unsigned int, coordonnée comprise entre 0 et 7
		*/
			unsigned int getChoiceInt();

		/**
		* @brief Affiche le plateau dans le terminal
		*/
			void printBoard();

		/**
		* @brief Lance le début d'une partie
		*/

			void startGame();
};

#endif // __CHESS_HPP__