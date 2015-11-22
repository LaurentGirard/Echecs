/**
 * @file Player.hpp
 * @author P. Sullivan, G.Laurent
 * @since 25/12/2015
 * @brief Définition de la classe Player
 *
**/

#ifndef __Player_HPP__
#define __Player_HPP__

#include "State.hpp"
#include "Piece.hpp"

class Player
{
	private:

		std::string _name;				// Attribut : nom du joueur
		std::string _color;				// Attribut : couleur du joueur
		Piece* _pieces[16];				// Attribut : pièces du joueur par indice (Pions: 0->7; Tours: 8,15; Cavaliers: 9,14; Fous: 10,13; Reine: 11, Roi: 12) cf ordre plateau

		State *_state;					// Attribut : état courant du joueur dans la partie
		State *_gameState;				// Attribut : état en jeu
		State *_checkState;				// Attribut : état d'échec
		State *_mateState;				// Attribut : état d'échec et mat
		State *_nullState;				// Attribut : état de jeu nul
		State *_endState;				// Attribut : état de fin de jeu

	public:

	/**
   	* @brief Destructeur de Player
   	* @param name, nom du joueur
  	 */
		Player(std::string name, std::string color);

	/**
   	* @brief Destructeur de Player
  	 */
		~Player();

	/**
	* @brief Permet de passer le joueur en état de jeu "normal"
	*/
		void inGame();

	/**
	* @brief Permet de passer le joueur en état d'Echec
	*/
		void check();

	/**
	* @brief Permet de passer le joueur en état d'Echec et Mat
	*/
		void checkMate();

	/**
	* @brief Permet de passer le joueur en état de partie nulle
	*/
		void gameNull();

	/**
	* @brief Permet de passer le joueur en état de partie finie
	*/
		void gameEnd();

	/**
	* @brief Affiche l'état courant du joueur sur la sortie standard
	*/
		void printState();

	/**
	* @brief Affiche l'ensemble des pièces encore en vie avec leurs coordonnées respectives
	*/
		void printPieces();

	/**
	* @brief Permet au joueur de selectionner une pièce qu'il possède
	* @param unsigned int x, coordonnée x de la case selectionnée
	* @param unsigned int y, coordonnée y de la case selectionnée
	* @return Piece* pointeur de la pièce selectionnée (null si coordonnées invalides)
	*/
		Piece* selectPiece( unsigned int x, unsigned int y);

	/**
	* @brief Getter de l'attribut _name
	* @return attribut _name
	*/
		std::string getName();

	/**
	* @brief Setter de l'attribut _name
	* @param newName, nouveau nom
	*/
		void setName(std::string newName);

	/**
	* @brief Getter de l'attribut _color
	* @return attribut _color
	*/
		std::string getColor();

	/**
	* @brief Getter de l'attribut _pieces
	* @return attribut _pieces
	*/
		Piece** getPieces();

	/**
	* @brief Getter de l'attribut *_state
	* @return attribut *_state
	*/
		State* getState();

	/**
	* @brief Setter de l'attribut *_state
	* @param newName, nouveau nom
	*/
		void setState(State *newState);
	/**
	* @brief Getter de l'attribut *gameState
	* @return attribut *gameState
	*/
		State* getGameState();

	/**
	* @brief Getter de l'attribut *_checkState
	* @return attribut *_checkState
	*/
		State* getCheckState();

	/**
	* @brief Getter de l'attribut *_mateState
	* @return attribut *_mateState
	*/
		State* getMateState();

	/**
	* @brief Getter de l'attribut *_nullState
	* @return attribut *_nullState
	*/
		State* getNullState();

	/**
	* @brief Getter de l'attribut *_endState
	* @return attribut *_endState
	*/
		State* getEndState();

	/**
	* @brief permet de retourner la piece roi
	* @return piece* pointeur de la piece roi
	*/
		Piece* getking();

	/**
	* @brief permet de savoir si le joueur se trouve en en checkmate
	* @return bool
	*/
		bool ischeckmate();

	/**
	* @brief permet de savoir si le joueur se trouve en en check
	* @return bool
	*/
		bool ischeck();

	/**
	* @brief permet de savoir si le joueur se trouve en en partie nulle
	* @return bool
	*/
		bool isnulle();
};

#endif // __Player_HPP__
