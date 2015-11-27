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
		* @param Piece* selectedP, pointeur vers la pièce selectionnée
		* @param Piece* selectedD, pointeur vers la pièce représentant la destination
		* @param Piece* pieceaeviter = NULL, pointeur vers la pièce représentant une piece a éviter
		* @param Piece* pieceD = NULL , pointeur vers la pièce représentant la destination virtuel

		* @return bool, vrai s'il n'y a pas de collision, faux sinon
		*/
			bool noCollision(Piece* selectedP, Piece* selectedD, Piece* pieceaeviter, Piece* pieceD);

		/**
		* @brief Effectue le déplacement de la pièce selectionnée vers la destination
		* @param Piece* selectedP, pointeur vers la pièce selectionnée
		* @param Piece* selectedD, pointeur vers la pièce représentant la destination
		*/
			void movePiece(Piece* selectedP, Piece* selectedD);

		/**
		* @brief Effectue le tour d'un joueur
		* @param Player* playerIG, Joueur actuellement en jeu
		* @param Player* adver, Joueur en attente de jouer
		* @return bool ( true si le joueur veut arreter de joueur)
		*/
			bool gameRound(Player* playerIG, Player* adver);

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
		* @brief Permet de savoir si un joueur se trouve en position d'echec
		* @param Player* playerIG, joueur actuellement en jeu
		* @param Player* adver, joueur adversaire
		* @return bool
		*/
		
		bool testEchec(Player* playerIG, Player* adver); 

		/**
		* @brief Permet de savoir si une piece se trouve en position d'echec
		* @param Piece* playerIG, pointeur d'une piece
		* @param Player* adver, joueur adversaire
		* @return bool
		*/
		
		bool testEchec(Piece* selectedP, Player* adver); 

		/**
		* @brief Permet de savoir si un joueur se trouve en position d'echec et mat
		* @param Player* playerIG, joueur actuellement en jeu
		* @param Player* adver, joueur adversaire
		* @return bool
		*/
		
		bool testEchecMat(Player* playerIG, Player* adver);

		/**
		* @brief Permet de savoir si la pieceD est sur le passage de la piece qui peut manger le roi
		* @param Player* playerIG, joueur actuellement en jeu
		* @param Piece* pieceD, pointeur d'une piece qui sera une destination
		* @param Player* advers, joueur adversaire
		* @return bool
		*/
		
		bool onTheWay(Player* playerIG, Piece* pieceD, Player* advers);

		/**
		* @brief Permet de retourner une liste de pieces de l'advers qui peut manger la piece selectedP
		* @param Piece* selectedP, pointeur d'une piece
		* @param Player* advers, joueur adversaire
		* @return liste de piece
		*/
		std::vector<Piece*> listPieces(Piece* selectedP, Player* advers);

		/**
		* @brief Permet de retourner un bool si une des pieces que peut manger la piece selected peut aller manger le roi du playerIG si la piece selectedP bouge
		* @param vector<Piece*> list, vecteur d'une liste de pièce
		* @param Player* advers, joueur adversaire
		* @param Player* playerIG, joueur actuellement en jeu
		* @param Piece* selectedP, pointeur d'une piece
		* @param Piece* selectedD, pointeur d'une piece
		* @return bool
		*/
		bool listCanEatKing(std::vector<Piece*> list, Player* advers, Player* playerIG, Piece* selectedP,Piece* selectedD);
		
		/**
		* @brief Procédure permettant de transformer le spawn
		* @param Player* playerIG, joueur actuellement en jeu
		* @param Piece* selectedP, pointeur d'une piece
		* @param Piece* selectedD, pointeur d'une piece
		*/
		void transfoSpawn(Player* playerIG, Piece* selectedP, Piece* selectedD);

		/**
		* @brief fonction permettant de savoir si le petit roque est possible
		* @param Player* playerIG, joueur actuellement en jeu
		* @param Piece* selectedP, pointeur d'une piece
		* @param Piece* selectedD, pointeur d'une piece
		*/
		bool tryCastling(Player* playerIG,Piece* selectedP,Piece* selectedD);

		/**
		* @brief fonction permettant de savoir si le grand roque est possible
		* @param Player* playerIG, joueur actuellement en jeu
		* @param Piece* selectedP, pointeur d'une piece
		* @param Piece* selectedD, pointeur d'une piece
		*/
		bool tryGCastling(Player* playerIG,Piece* selectedP,Piece* selectedD);

		/**
		* @brief Procédure permettant de faire le petit roque
		* @param Player* playerIG, joueur actuellement en jeu
		*/
		void castling(Player* playerIG);

		/**
		* @brief Procédure permettant de faire le grand roque
		* @param Player* playerIG, joueur actuellement en jeu
		*/
		void gCastling(Player* playerIG);
		
		/**
		* @brief fonction permettant de savoir si une piece appartient au player IG
		* @param Piece* piece, pointeur vers une piece
		* @param Player* playerIG, joueur actuellement en jeu
		* @return bool
		*/
		bool isPieceIn(Piece* piece, Player* playerIG);
	
		/**
		* @brief fonction permettant de savoir si la partie se trouve en partie nulle
		* @return bool
		*/
		bool isNull();

		/**
		* @brief Lance le début d'une partie
		*/
		void startGame();
};

#endif // __CHESS_HPP__
